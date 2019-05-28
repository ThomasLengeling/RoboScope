#include <stdio.h>
#include "M451Series.h"

#define PLL_CLOCK       48000000

STR_CANMSG_T tMsg;
STR_CANMSG_T rrMsg;


void CAN0_IRQHandler(void)
{
	STR_CANMSG_T* Msg;
    uint32_t u8IIDRstatus, i;
    uint8_t u8Data;

    u8IIDRstatus = CAN0->IIDR;

    if(u8IIDRstatus == 0x00008000)        /* Check Status Interrupt Flag (Error status Int and Status change Int) */
    {
        /**************************/
        /* Status Change interrupt*/
        /**************************/
        if(CAN0->STATUS & CAN_STATUS_RXOK_Msk)
        {
            CAN0->STATUS &= ~CAN_STATUS_RXOK_Msk;   /* Clear RxOK status*/
        }

        if(CAN0->STATUS & CAN_STATUS_TXOK_Msk)
        {
            CAN0->STATUS &= ~CAN_STATUS_TXOK_Msk;    /* Clear TxOK status*/
        }

        /**************************/
        /* Error Status interrupt */
        /**************************/
        if(CAN0->STATUS & CAN_STATUS_BOFF_Msk)
        {
            UART_Write(UART3, "BOFF INT\r\n", 10) ;
        }
        else if(CAN0->STATUS & CAN_STATUS_EWARN_Msk)
        {
        	UART_Write(UART3, "EWARN INT\r\n", 11) ;
        }
        else if((CAN0->ERR & CAN_ERR_TEC_Msk) != 0)
        {
        	UART_Write(UART3, "Transmit error!\r\n", 17) ;
        }
        else if((CAN0->ERR & CAN_ERR_REC_Msk) != 0)
        {
        	UART_Write(UART3, "Receive error!\r\n", 16) ;
        }

    }
    else if(u8IIDRstatus != 0)
    {
    	CAN_Receive(CAN0, MSG(0), &rrMsg);

    	Msg = &rrMsg;

        for(i = 0; i < Msg->DLC; i++)
        {
        	u8Data = Msg->Data[i];

        	/* Print hexadecimal format */
        	UART_Write(UART3, "0x", 2);

        	if((u8Data>>4)>9)
        		UART_WRITE(UART3, ((u8Data>>4)%10)+65);
        	else
        		UART_WRITE(UART3, (u8Data>>4)+48);

        	if((u8Data&0xf)>9)
        		UART_WRITE(UART3, (u8Data%10)+65);
        	else
        		UART_WRITE(UART3, (u8Data&0xf)+48);

        	UART_Write(UART3, " ", 1);
        }

        UART_Write(UART3, "\r\n", 2);

        CAN_CLR_INT_PENDING_BIT(CAN0, (u8IIDRstatus - 1)); /* Clear Interrupt Pending */
    }
    else if(CAN0->WU_STATUS == 1)
    {
    	UART_Write(UART3, "Wake up\r\n", 9);

        CAN0->WU_STATUS = 0;    /* Write '0' to clear */
    }

}


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable HIRC clock (Internal RC 22.1184MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Wait for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Select HCLK clock source as HIRC and and HCLK source divider as 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Set PLL to Power-down mode and PLLSTB bit in CLK_STATUS register will be cleared by hardware.*/
    CLK_DisablePLL();

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART3_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));

    /* Enable CAN module clock */
    CLK_EnableModuleClock(CAN0_MODULE);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set PA multi-function pins for UART3 RXD and TXD, and Clock Output */
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA8MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA8MFP_UART3_TXD | SYS_GPA_MFPH_PA9MFP_UART3_RXD);

    /* Set PA multi-function pins for CANTX0, CANRX0 */
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA12MFP_CAN0_TXD | SYS_GPA_MFPH_PA13MFP_CAN0_RXD);


}


int main()
{

	/* Unlock protected registers */
    SYS_UnlockReg();

    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Set CAN bus transceiver to high speed mode */
	PA->MODE = (PA->MODE & (~GPIO_MODE_MODE1_Msk)) | (GPIO_MODE_OUTPUT << GPIO_MODE_MODE1_Pos);
	PA1 = 0;

    /* Init UART3 to 115200-8n1 for print message */
    UART_Open(UART3, 115200);

    UART_Write(UART3, "CAN bus Tx test.\r\n", 18);

    /* Init CAN0 1Mbps */
    CAN_Open(CAN0, 1000000, CAN_NORMAL_MODE);

    /* Enable CAN interrupt and corresponding NVIC of CAN */
    CAN_EnableInt(CAN0, CAN_CON_IE_Msk | CAN_CON_SIE_Msk);
    NVIC_SetPriority(CAN0_IRQn, (1 << __NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(CAN0_IRQn);

    /* Send a 11-bit Standard Identifier message */
    tMsg.FrameType = CAN_DATA_FRAME;
    tMsg.IdType   = CAN_STD_ID;
    tMsg.Id       = 0x7FF;
    tMsg.DLC      = 2;
    tMsg.Data[0]  = 0x07;
    tMsg.Data[1]  = 0xFF;

    /* Configure Msg RAM and send the Msg in the RAM */
    if(CAN_Transmit(CAN0, MSG(0), &tMsg) == FALSE)
    	UART_Write(UART3, "Set Tx Msg Object 0 failed.\r\n", 29);

    while(1);

}

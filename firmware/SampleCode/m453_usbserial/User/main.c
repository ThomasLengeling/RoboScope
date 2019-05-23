/******************************************************************************
 * @file     main.c
 * @brief
 *           Implement a USB virtual COM port device.
 *            It supports one virtual COM port.
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "M451Series.h"
#include "cdc_serial.h"

#define PLL_CLOCK		24000000


/*--------------------------------------------------------------------------*/
STR_VCOM_LINE_CODING gLineCoding = {115200, 0, 0, 8};   /* Baud rate : 115200    */
/* Stop bit     */
/* parity       */
/* data bits    */
uint16_t gCtrlSignal = 0;     /* BIT0: DTR(Data Terminal Ready) , BIT1: RTS(Request To Send) */

/*--------------------------------------------------------------------------*/
#define RXBUFSIZE           384 /* RX buffer size */
#define TXBUFSIZE           128 /* TX buffer size */

#define TX_FIFO_SIZE        16  /* TX Hardware FIFO size */


/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
/* UART3 */
volatile uint8_t comRbuf[RXBUFSIZE];
volatile uint16_t comRbytes = 0;
volatile uint16_t comRhead = 0;
volatile uint16_t comRtail = 0;

volatile uint8_t comTbuf[TXBUFSIZE];
volatile uint16_t comTbytes = 0;
volatile uint16_t comThead = 0;
volatile uint16_t comTtail = 0;

volatile uint32_t gu32RxSize = 0;
volatile uint32_t gu32TxSize = 0;



/*--------------------------------------------------------------------------*/


void SYS_Init(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable Internal RC 22.1184MHz clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for Internal RC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to Internal RC and set HCLK divider to 1 */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable module clock */
    CLK_EnableModuleClock(UART3_MODULE);
    CLK_EnableModuleClock(USBD_MODULE);

    /* Select module clock source */
    CLK_SetModuleClock(UART3_MODULE, CLK_CLKSEL1_UARTSEL_HXT, CLK_CLKDIV0_UART(1));
    CLK_SetModuleClock(USBD_MODULE, 0, CLK_CLKDIV0_USB(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and cyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Enable USB LDO33 */
    SYS->USBPHY = SYS_USBPHY_LDO33EN_Msk;

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set GPA multi-function pins for UART3 RXD and TXD, and Clock Output */
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA8MFP_Msk | SYS_GPA_MFPH_PA9MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA8MFP_UART3_TXD | SYS_GPA_MFPH_PA9MFP_UART3_RXD);
}


void UART3_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART3_RST);

    /* Configure UART3 and set UART3 Baudrate */
    UART_Open(UART3, 115200);

    /* Enable UART3 RX Time-Out Interrupt and RX Data Available Interrupt */
    UART_EnableInt(UART3, UART_INTEN_RXTOIEN_Msk | UART_INTEN_RDAIEN_Msk);
}


/*---------------------------------------------------------------------------------------------------------*/
/* UART Callback function                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void UART3_IRQHandler(void)
{
    uint32_t u32IntStatus;
    uint8_t bInChar;
    int32_t size;
    uint8_t *u8Ptr;

    u32IntStatus = UART3->INTSTS;

    if((u32IntStatus & 0x1 /* RDAIF */) || (u32IntStatus & 0x10 /* TOUT_IF */))
    {
        /* Receiver FIFO threshold level is reached or Rx time out */

        /* Get all the input characters */
        while((UART3->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk) == 0)
        {
            /* Check if buffer full */
            if(comRbytes < RXBUFSIZE)
            {
                /* Get the character from UART Buffer */
                bInChar = UART3->DAT;
                /* Enqueue the character */
                comRbuf[comRtail++] = bInChar;
                if(comRtail >= RXBUFSIZE)
                    comRtail = 0;
                comRbytes++;
            }
            else
            {
            	/* Release buffer if full */
            	if(gu32TxSize == 0)
            	{
            		size = EP2_MAX_PKT_SIZE;

                    /* Get EP2 buffer address */
                    u8Ptr = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));

                    while(size)
                    {
                        bInChar = comRbuf[comRhead++];
                        u8Ptr[EP2_MAX_PKT_SIZE-size] = comRbuf[comRhead++];
                        if(comRhead >= RXBUFSIZE)
                            comRhead = 0;
                        comRbytes--;
                        size--;
                    }

                    gu32TxSize = EP2_MAX_PKT_SIZE;
                    USBD_SET_PAYLOAD_LEN(EP2, EP2_MAX_PKT_SIZE);
            	}

            	break;

            }
        }
    }

    if(u32IntStatus & UART_INTSTS_THREINT_Msk)
    {

        if(comTbytes)
        {
            /* Fill the Tx FIFO */
            size = comTbytes;
            if(size >= TX_FIFO_SIZE)
            {
                size = TX_FIFO_SIZE;
            }

            while(size)
            {
                bInChar = comTbuf[comThead++];
                UART3->DAT = bInChar;
                if(comThead >= TXBUFSIZE)
                    comThead = 0;
                comTbytes--;
                size--;
            }
        }
        else
        {
            /* No more data, just stop Tx (Stop work) */
            UART3->INTEN &= (~UART_INTEN_THREIEN_Msk);
        }
    }

}

void VCOM_TransferData(void)
{
    int32_t i, i32Len;
    uint8_t *u8Ptr;

    /* Mask all interrupt */
    __set_PRIMASK(1);

    /* Check wether USB is ready for next packet or not*/
    if(gu32TxSize == 0)
    {
        /* Check wether we have new COM Rx data to send to USB or not */
        if(comRbytes)
        {
            i32Len = comRbytes;
            if(i32Len > EP2_MAX_PKT_SIZE)
                i32Len = EP2_MAX_PKT_SIZE;

            /* Get EP2 buffer address */
            u8Ptr = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));

            for(i = 0; i < i32Len; i++)
            {
            	u8Ptr[i] = comRbuf[comRhead++];
                if(comRhead >= RXBUFSIZE)
                    comRhead = 0;
            }

            comRbytes -= i32Len;

            gu32TxSize = i32Len;
            USBD_SET_PAYLOAD_LEN(EP2, i32Len);
        }
        else
        {
            /* Prepare a zero packet if previous packet size is EP2_MAX_PKT_SIZE and 
               no more data to send at this moment to note Host the transfer has been done */
            i32Len = USBD_GET_PAYLOAD_LEN(EP2);
            if(i32Len == EP2_MAX_PKT_SIZE)
                USBD_SET_PAYLOAD_LEN(EP2, 0);
        }
    }

    /* Process the Bulk out data when bulk out data is ready. */
    if(gu32RxSize && (gu32RxSize <= TXBUFSIZE - comTbytes))
    {
    	/* Get EP3 buffer address */
    	u8Ptr = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP3));

        for(i = 0; i < gu32RxSize; i++)
        {
            comTbuf[comTtail++] = u8Ptr[i];
            if(comTtail >= TXBUFSIZE)
                comTtail = 0;
        }

        comTbytes += gu32RxSize;

        gu32RxSize = 0;

        /* Ready to get next BULK out */
        USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
    }

    /* Process the software Tx FIFO */
    if(comTbytes)
    {
        /* Check if Tx is working */
        if((UART3->INTEN & UART_INTEN_THREIEN_Msk) == 0)
        {
            /* Send one bytes out */
            UART3->DAT = comTbuf[comThead++];
            if(comThead >= TXBUFSIZE)
                comThead = 0;

            comTbytes--;

            /* Enable Tx Empty Interrupt. (Trigger first one) */
            UART3->INTEN |= UART_INTEN_THREIEN_Msk;
        }
    }

    /* Restore interrupt */
    __set_PRIMASK(0);

}


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    SYS_Init();
    UART3_Init();

    USBD_Open(&gsInfo, VCOM_ClassRequest, NULL);

    /* Endpoint configuration */
    VCOM_Init();
    USBD_Start();
    NVIC_EnableIRQ(USBD_IRQn);
    NVIC_EnableIRQ(UART3_IRQn);

    while(1)
    {
        VCOM_TransferData();
    }
}



/*** (C) COPYRIGHT 2014 Nuvoton Technology Corp. ***/


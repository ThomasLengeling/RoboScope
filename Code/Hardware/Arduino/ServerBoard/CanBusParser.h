/*
   Class that manages CAN Bus Communication protocol
*/
#ifndef CAN_BUS_PARSER_H
#define CAN_BUS_PARSER_H

#include <FlexCAN.h>

/*
 * Teensy available speeds:
 * https://www.pjrc.com/teensy/td_uart.html
 * 
 * 2000000
 * 1000000
 * 250000 
 * 115200
 * 38400
 */
 
#define SERIAL_BAU    1000000 
 
#define SPPED_BUS     1000000
#define MSG_LENGTH    8

  /*
   * Msg structure
   * [0] : motorID
   * [1] : motorDir
   * [2] : motorStep
   * [3] : motorTimeActivation
   * [4] : motorEnable
   * [5] : color
   * [6] : motorSensor0
   * [7] : motorSensor1
  */



//---------------------------------------------------------
class CanBusParser {
  public:
    //constructor
    CanBusParser();

    //msg
    void sendMsg();
    void readMsg();

    //update msg from an input msg
    void updateMsg(uint8_t message[]);
    void getRxMsg(uint8_t msg[]);

    //dump msg
    void hexDump(uint8_t dumpLen, uint8_t *bytePtr);
    void writeMsgToSerial();

    //activate and send msg
    void blockMsg();

    //activate
    void activateMsg();
    void deactivateMsg();
    boolean isActiveMsg();
    
  private:

    FlexCAN * canBus;

    boolean   activeMsg;

    CAN_message_t txMsg;
    CAN_message_t rxMsg;
};

#endif

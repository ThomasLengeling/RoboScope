/*
   Class that manages CAN Bus Communication protocol
*/
#ifndef CAN_BUS_PARSER_H
#define CAN_BUS_PARSER_H

#include <FlexCAN.h>

#define SPPED_BUS     1000000

class CanBusParser {
  public:
    //constructor
    CanBusParser();

    void sendMsg();
    void updatMsg();

    //update msg
    void waitforMsg();

    //dump msg
    int hexDump(uint8_t dumpLen, uint8_t *bytePtr);

  private:

    FlexCAN * canBus;

    CAN_message_t txMsg;
    CAN_message_t rxMsg;
};

#endif

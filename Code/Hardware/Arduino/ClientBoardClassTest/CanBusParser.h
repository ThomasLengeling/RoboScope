/*
 * Class that manages CAN Bus Communication protocol 
 */
#ifndef CAN_BUS_PARSER_H
#define CAN_BUS_PARSER_H

#include <FlexCAN.h>

class CanBusParser {
  public:
    CanBusParser();

    void sendMsg();
    void updatMsg();
  private:

  FlexCAN * canBus;
  
  CAN_message_t txMsg;
  CAN_message_t rxMsg;
};

#endif

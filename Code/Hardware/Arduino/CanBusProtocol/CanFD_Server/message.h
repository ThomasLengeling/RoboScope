#pragma once

#include "arduino.h"
#include <FlexCAN_T4.h>

/*
 * 
 * 
 * CAN BUS FD has a 64 msg protocol.
 *  - 8 motor per msg
 * CAN BUS 2.0 has a 8 byte msg protocol
 *  - 2 motors per msg
 * 
 * Messsage Protocol:
 * 4 bytes:
 *    2 bytes for color
 *    1 byte for rod position 0 - 255
 *    1 byte -> 00000000
 *        8 bits:
 *          0
 *          1
 *          2
 *          3
 *          4
 *          5
 *          6
 *          7
 */
class Message {
  public:
 
    Message(int board_des);

    //add motor message
    void addMotorMessage(int des, uint8_t color[], uint8_t steps, uint8_t interaction);
    CANFD_message_t returnCANmessage();

    // create interaction byte msg
    uint8_t createInteractionMsg();

    //generate the motor byte msg
    uint8_t createMotorMsg();

    //generate the color byte msg
    uint8_t * createColorMsg();
    
  private:
    int msg_count = 0;
     CANFD_message_t msg;
};

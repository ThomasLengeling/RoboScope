#include "message.h"
#include "functions.h"

Message::Message(int board_des) {
   this->msg.id = board_des;
}

void Message::addMotorMessage(int des, uint8_t color[], uint8_t steps, uint8_t interaction) {
  uint16_t two_color = (((color[0] & 0b11111000)<<8) + ((color[1] & 0b11111100)<<3)+(color[2]>>3));
  uint8_t colors[2] = {convertFrom16To8(two_color)};
  uint8_t msg[4] = {colors[0], colors[1], steps, interaction};
  memcpy(this->msg.buf + des*4, msg, 4);
}

CANFD_message_t Message::returnCANmessage() {
  this->msg.len = 64;
  return this->msg;
}

uint8_t* convertFrom16To8(uint16_t dataAll, uint8_t* rgb) {
    rgb[0] = dataAll >> 8;
    rgb[1] = dataAll & 0x00FF;
    return rgb;
}

class Message {
  public:
    CANFD_message_t msg;
    Message(int board_des);
    void addMotorMessage(int des, uint8_t color[], uint8_t steps, uint8_t interaction);
    CANFD_message_t returnCANmessage();
  private:
    int msg_count = 0;
};

Message::Message(int board_des) {
   this->msg.id = board_des;
}

void Message::addMotorMessage(int pixel_des, uint8_t* color, uint8_t steps, uint8_t interaction) {
  uint16_t two_color = (((color[0] & 0b11111000)<<8) + ((color[1] & 0b11111100)<<3)+(color[2]>>3));
  uint8_t rgb[2]= {0};
  convertFrom16To8(two_color, rgb);
  uint8_t msg[4] = {rgb[0],rgb[1], steps, interaction};
  memcpy(this->msg.buf + pixel_des*4, msg, 4); 
}

CANFD_message_t Message::returnCANmessage() {
  this->msg.len = 64;
  return this->msg;
}

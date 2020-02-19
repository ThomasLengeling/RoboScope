uint16_t convertFrom8To16(uint8_t dataFirst, uint8_t dataSecond) {
    uint16_t dataBoth = 0x0000;

    dataBoth = dataFirst;
    dataBoth = dataBoth << 8;
    dataBoth |= dataSecond;
    return dataBoth;
}

uint8_t* convertFrom16To8(uint16_t dataAll) {
    static uint8_t arrayData[2] = { 0x00, 0x00 };

    *(arrayData) = (dataAll >> 8) & 0x00FF;
    arrayData[1] = dataAll & 0x00FF;
    return arrayData;
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

void Message::addMotorMessage(int des, uint8_t color[], uint8_t steps, uint8_t interaction) {
  uint16_t two_color = (((color[0] & 0b11111000)<<8) + ((color[1] & 0b11111100)<<3)+(color[2]>>3));
  uint8_t colors[2] = {convertFrom16To8(two_color)};
  uint8_t msg[4] = {colors[0],colors[1], steps, interaction};
  memcpy(this->msg.buf + des*4, msg, 4); 
}

CANFD_message_t Message::returnCANmessage() {
  this->msg.len = 64;
  return this->msg;
}

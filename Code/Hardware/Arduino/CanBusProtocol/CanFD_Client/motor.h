uint16_t convertFrom8To16(uint8_t dataFirst, uint8_t dataSecond) {
    uint16_t dataBoth;
    dataBoth = (dataFirst << 8) | dataSecond;
    return dataBoth;
}

class Motor {
  public:
    Motor(int board_des);
    uint8_t* read_msg(uint8_t* color, CANFD_message_t msg);
    void setLED();
    uint8_t* returnColor(uint8_t* colors);
  private:
    int local_name;
    int index;
    int state;
    uint16_t color;
    uint8_t steps;
    uint8_t interaction;
};

Motor::Motor(int board_des) {
   this->local_name = board_des;
   this->index = board_des*4;
   pinMode(13,OUTPUT);
   this->state = HIGH;
   digitalWrite(13,state);
}

uint8_t* Motor::read_msg(uint8_t* colors, CANFD_message_t msg) {
  if (msg.id-1 <= this->local_name && msg.id+15>this->local_name) {
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print("  TS: "); Serial.println(msg.timestamp);
    for (int i = this->index; i<this->index+4; i++) {
      Serial.print(msg.buf[i]); Serial.print(" "); 
    }
    Serial.println(" ");
    this->color = convertFrom8To16(msg.buf[this->index],msg.buf[this->index+1]);
    this->steps = msg.buf[this->index+2];
    this->interaction = msg.buf[this->index+3];
    this->setLED();
    return this->returnColor(colors);
  }
}

void Motor::setLED() {
  if (this->state==HIGH) {
    this->state=LOW;
  } else {
    this->state=HIGH;
  }
  digitalWrite(13,this->state);
}

uint8_t* Motor::returnColor(uint8_t* colors) {
  colors[0] = ((((this->color >> 11) & 0x1F) * 527) + 23) >> 6;
  colors[1] = ((((this->color >> 5) & 0x3F) * 259) + 33) >> 6;
  colors[2] = (((this->color & 0x1F) * 527) + 23) >> 6;
 
  return colors;
}

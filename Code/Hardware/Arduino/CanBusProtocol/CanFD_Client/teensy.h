#include "motor.h"

class Teensy {
  public:
    Teensy(int board_des);
    uint8_t* read_msg(CANFD_message_t msg);
    void setLED();
    CANFD_message_t write_msg();
  private:
    int local_name;
    const byte NEO_PIN[8] = {16, 17, 2, 3,4, 24, 25, 13};
    const Motor motors[8] = {Motor(0, NEO_PIN[0]),Motor(1, NEO_PIN[1]),Motor(2, NEO_PIN[2]),
                             Motor(3, NEO_PIN[3]),Motor(4, NEO_PIN[4]),Motor(5, NEO_PIN[5]),
                             Motor(6, NEO_PIN[6]),Motor(7, NEO_PIN[7])};
    int state;
};

Teensy::Teensy(int board_des) {
   this->local_name = board_des;
   this->state = HIGH;
   pinMode(13,OUTPUT);
   digitalWrite(13,state);
}

uint8_t* Teensy::read_msg(CANFD_message_t msg) {
  if (msg.id==this->local_name) {
    for (int i =0; i<64;i++) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.println(" ");
    for (int i = 0; i<32; i+=4) {
      uint16_t color = convertFrom8To16(msg.buf[i],msg.buf[i+1]);
      motors[i/4].update(color, msg.buf[i+2], msg.buf[i+3]);
    }
    this->setLED();
  }
}

void Teensy::setLED() {
  if (this->state==HIGH) {
    this->state=LOW;
  } else {
    this->state=HIGH;
  }
  digitalWrite(13,this->state);
}

CANFD_message_t Teensy::write_msg() {
  CANFD_message_t msg;
  uint8_t rgb[2]= {0};
  msg.id = 0xFFFFFFFF;
  return msg;
}

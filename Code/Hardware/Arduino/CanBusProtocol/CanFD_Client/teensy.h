#include "motor.h"
#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

class Teensy {
  public:
    Teensy(int board_des, SX1509 sx01, SX1509 sx02);
    CANFD_message_t read_msg(CANFD_message_t msg);
    void setLED();
    CANFD_message_t write_msg(uint8_t* buf);
    CANFD_message_t motor_update();
  private:
    int local_name;
    const byte SWITCH[8] = {8, 6, 9, 7, 8, 6, 9, 7};
    const byte DOWN[8] = {12, 4, 15, 5, 12, 4, 15, 5};
    const byte UP[8] = {11, 3, 14, 1, 11, 3, 14, 1};
    const byte TOUCH[8] = {10, 2, 13, 0, 10, 2, 13, 0};
    const byte NEO_PIN[8] = {16, 17, 2, 3,4, 24, 25, 13};
    const byte SX1509_ADDRESS_01 = 0x3F;
    const byte SX1509_ADDRESS_11 = 0x70;
    const Motor motors[8] = {Motor(0, NEO_PIN[0], SWITCH[0], DOWN[0], UP[0], TOUCH[0]),
                             Motor(1, NEO_PIN[1], SWITCH[1], DOWN[1], UP[1], TOUCH[1]),
                             Motor(2, NEO_PIN[2], SWITCH[2], DOWN[2], UP[2], TOUCH[2]),
                             Motor(3, NEO_PIN[3], SWITCH[3], DOWN[3], UP[3], TOUCH[3]),
                             Motor(4, NEO_PIN[4], SWITCH[4], DOWN[4], UP[4], TOUCH[4]),
                             Motor(5, NEO_PIN[5], SWITCH[5], DOWN[5], UP[5], TOUCH[5]),
                             Motor(6, NEO_PIN[6], SWITCH[6], DOWN[6], UP[6], TOUCH[6]),
                             Motor(7, NEO_PIN[7], SWITCH[7], DOWN[7], UP[7], TOUCH[7])};
    int state;
};

Teensy::Teensy(int board_des, SX1509 sx01, SX1509 sx02) {
   this->local_name = board_des;
   this->state = HIGH;
   
   if (!sx01.begin(this->SX1509_ADDRESS_01) ) {
    Serial.println("Failed 01");
    Serial.println(this->SX1509_ADDRESS_01);
   } else {
    Serial.println("Connected 1");
   }

   if (!sx02.begin(this->SX1509_ADDRESS_11)) {
     Serial.println("Failed sx 2");
     Serial.println(this->SX1509_ADDRESS_11);
   } else {
     Serial.println("Connected 2");
   }
   
   for (int i = 0; i < 4; i++) {
      this->motors[i].update_sx(sx01);
   }

   for (int i = 4; i < 8; i++) {
      this->motors[i].update_sx(sx02);
   }
   
   pinMode(13,OUTPUT);
   digitalWrite(13,state);
}

CANFD_message_t Teensy::read_msg(CANFD_message_t msg) {
  if (msg.id==this->local_name) {
    for (int i = 0; i<32; i+=4) {
      uint16_t color = convertFrom8To16(msg.buf[i],msg.buf[i+1]);
      motors[i/4].msg_update(color, msg.buf[i+2], msg.buf[i+3]);
    }
    this->setLED();
    return this->write_msg(msg.buf);
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

CANFD_message_t Teensy::write_msg(uint8_t* buf) {
  CANFD_message_t msg;
  uint8_t rgb[2]= {0};
  msg.id = 0xFFFFFFFF;
  msg.len = 64;
  for (int i=0; i<64; i++){
    Serial.print(buf[i]); Serial.print(" ");
    msg.buf[i]=buf[i];
  }
  return msg;
}

CANFD_message_t Teensy::motor_update() {
  bool new_msg = false;
  CANFD_message_t msg;
  msg.id = 0xFFFFFFFF;
  msg.len = 64;
  for (int i = 0; i < 8; i++) {
     bool change = this->motors[i].led_switch_handle();
     bool change2 = this->motors[i].limit_switch_handle();
     if (change || change2) {
        new_msg = true;
     }
  }

  if (new_msg) {
    return msg;
  }
}

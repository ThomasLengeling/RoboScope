#include <FlexCAN_T4.h>
#include "message.h"
#include <string.h>
#define START 0
#define DOWN 1
#define UP 2

FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_64> FD;
int local_name = 3;
const int input_pin = 16;
uint8_t msg_array[64] = {2,0,3,4,5,6,7,8,7,8,9,9,1,1,5,12,31,14,19,20,24};

int state;
int num_count;
int down_initial;
int up_initial;
const int BUTTON_TIMEOUT=500;

void setup(void) {
  Serial.begin(115200); delay(500);
  FD.begin();
  CANFD_timings_t config;
  config.clock = CLK_24MHz;
  config.baudrate = 1000000;
  config.baudrateFD = 2000000;
  config.propdelay = 190;
  config.bus_length = 1;
  config.sample = 87.5;
  FD.setRegions(64);
  FD.setBaudRate(config);
  FD.mailboxStatus();
  
  pinMode(input_pin, INPUT_PULLUP);
  state = START;
  num_count = 0;
}

void loop() {
  number_fsm(digitalRead(input_pin));
}

void number_fsm(uint8_t input){
  switch(state){
    case START: 
      if (num_count!=0) {
        Serial.println(num_count);
        Serial.print("writing: "); Serial.print(millis());
        Serial.println(" ");
        Message msg = Message(num_count);
        uint8_t colors[3] = {0,255,255};
        msg.addMotorMessage(0,colors,01111000,01100011);
        msg.addMotorMessage(2,colors,01000000,00001011);
        msg.addMotorMessage(5,colors,01111110,01111111);
        msg.addMotorMessage(6,colors,01111110,01111111);
        FD.write(msg.returnCANmessage());
        num_count=0;
      }
             
      if (input==0){
        down_initial = millis();
        state = DOWN;
      }
      break; //don't forget break statements
    case DOWN:
      if ((millis()-down_initial)< BUTTON_TIMEOUT) {
        if (millis()-down_initial > 10 && input==1) {
          up_initial = millis();
          state = UP;
        }
      } else {
        state = START;
        Serial.println("start");
      }
      break;
    case UP:
      if ((millis()-up_initial)< BUTTON_TIMEOUT) {
        if (millis()-up_initial > 20 && input==0) {
          num_count++;
          down_initial = millis();
          state = DOWN;
        }
      } else {
        num_count++;
        state = START;
      }
      break;
  }
}

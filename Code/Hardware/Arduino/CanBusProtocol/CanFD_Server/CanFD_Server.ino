#include <FlexCAN_T4.h>
#include "message.h"
#include <string.h>
#define START 0
#define DOWN 1
#define UP 2

FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_64> FD;
int local_name = 3;
const int input_pin = 16;
uint8_t colors0[3] = {99, 63, 171};
uint8_t colors1[3] = {255, 0, 0};
uint8_t colors2[3] = {0, 255, 0};
uint8_t colors3[3] = {0, 0, 255};
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
  CANFD_message_t msg2;
  number_fsm(digitalRead(input_pin));
  if (FD.read(msg2)) { 
      Serial.print("from: "); Serial.print(msg2.buf[0]);  
      Serial.println(" ");
      for (int i = 1; i<msg2.len; i++) {
        Serial.print(msg2.buf[i]); Serial.print(" "); 
      }
      Serial.println(" ");
  }
}

void number_fsm(uint8_t input){
  switch(state){
    case START: 
      if (num_count!=0) {
        Serial.print("writing: "); Serial.print(millis());
        Serial.println(" ");
        Message msg = Message(9);
        if (num_count==1){
          for (int i =0; i<8; i++) {
            msg.addMotorMessage(i,colors3,255,255);
          }
        } else if (num_count==2){
          for (int i =0; i<8; i++) {
            msg.addMotorMessage(i,colors2,255,255);
          }
        } else if (num_count==3){
          for (int i =0; i<8; i++) {
            msg.addMotorMessage(i,colors1,255,255);
          }
        } else if (num_count==4){
          for (int i =0; i<8; i++) {
            msg.addMotorMessage(i,colors0,255,255);
          }
        }

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

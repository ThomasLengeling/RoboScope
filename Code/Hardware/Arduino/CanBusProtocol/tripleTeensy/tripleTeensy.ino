#include <FlexCAN_T4.h>
#define START 0
#define DOWN 1
#define UP 2

FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> FD;
int local_name = 3;
const int input_pin = 16;
int msg_array[8] = {1,0,3,4,5,6,7,8};

int state;
int num_count;
int down_initial;
int up_initial;
const int BUTTON_TIMEOUT=200;

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
  CANFD_message_t msg; 
  number_fsm(msg, digitalRead(input_pin));
//  if (FD.read(msg)) {
//    reading(msg);
//  }

}

void writing(CANFD_message_t msg, int des, int msg_array[]) {
  msg.len = 8; msg.id = des; 
  for (int i=0; i<8; i++) {
    msg.buf[i]=msg_array[i];
  }
  FD.write(msg);
}

void reading(CANFD_message_t msg) {
  if (msg.id==local_name) {
    if (msg.buf[0] ==99) {
      Serial.print("successfully received (from"); Serial.print(msg.buf[1]); Serial.print(")"); 
      Serial.println("");
    } else {
      Serial.print("MB: "); Serial.print(msg.mb);
      Serial.print("  ID: 0x"); Serial.print(msg.id);
      Serial.print("  EXT: "); Serial.print(msg.flags.extended );
      Serial.print("  LEN: "); Serial.print(msg.len);
      Serial.print(" DATA: ");
      for ( uint8_t i = 0; i < 8; i++ ) {
        Serial.print(msg.buf[i]); Serial.print(" ");
      }
      Serial.print("  TS: "); Serial.println(msg.timestamp);
      Serial.println(millis());
    }
  }
}

void number_fsm(CANFD_message_t msg, uint8_t input){
  switch(state){
    case START: 
      if (num_count!=0) {
        Serial.println(num_count);
        Serial.print("writing: "); Serial.print(millis());
        Serial.println(" ");
        writing(msg, num_count, msg_array);
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

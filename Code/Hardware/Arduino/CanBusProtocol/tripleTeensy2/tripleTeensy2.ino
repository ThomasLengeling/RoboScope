#include <FlexCAN_T4.h>

FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> FD;
int local_name = 2;
int msg_array[8]= {1,2,3,4,32,6,7,8};
int state;
uint32_t timer;
void setup(void) {
  Serial.begin(115200);
  delay(500);
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
  pinMode(13,OUTPUT);
  state = LOW;
  timer = millis();
}

void loop() {
  CANFD_message_t msg;
  if (FD.read(msg)!=0) { 
    Serial.println("reading");
    reading(msg, msg_array);
  }
}

void writing(CANFD_message_t msg, int des, int msg_array[]) {
  msg.len = 8; msg.id = des; 
  for (int i=0; i<9; i++) {
    msg.buf[i]=msg_array[i];
  }
  FD.write(msg);
}

void reading(CANFD_message_t msg, int msg_array[]) {
  if (msg.id==local_name) {
    Serial.print("MB: "); Serial.print(msg.mb);
    Serial.print("  ID: 0x"); Serial.print(msg.id);
    Serial.print("  EXT: "); Serial.print(msg.flags.extended );
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" DATA: ");
    for ( uint8_t i = 0; i < 8; i++ ) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.print("  TS: "); Serial.println(msg.timestamp);

    if (state==HIGH) {
      state=LOW;
    } else {
      state=HIGH;
    }
    digitalWrite(13,state);
    timer = millis();
  }
}

/*


*/
#include <FlexCAN_T4.h>
#include <string.h>

#include "message.h"


#define START 0
#define DOWN 1
#define UP 2

//FD CAN BUS
FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_64>     canBusFD;

//CAN BUS
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16>       canBus;  // can1 port

/*



*/

//key pins
const int KEY_PIN_01 = 6;
const int KEY_PIN_02 = 7;
const int KEY_PIN_03 = 8;
const int KEY_PIN_04 = 9;

const int LED_15 = 22;
const int LED_16 = 23;

//MOTOR ID
const int MOTOR_ID = 0;

uint8_t msg_array[64] = {2, 0, 3, 4, 5, 6, 7, 8, 7, 8, 9, 9, 1, 1, 5, 12, 31, 14, 19, 20, 24};

const int BUTTON_TIMEOUT = 500;

//----------------------------------------------------------------
void setup(void) {
  Serial.begin(115200);
  delay(500);


  Serial.println("Initializing CAN BUS Server");

  //CAN 0 BUS
  canBus.begin();
  canBus.setBaudRate(500000);     // 500kbps data rate
  canBus.enableFIFO();
  canBus.enableFIFOInterrupt();
  canBus.onReceive(FIFO, canSniff);
  canBus.mailboxStatus();


  //FD CAN BUS
  canBusFD.begin();
  CANFD_timings_t config;
  config.clock = CLK_24MHz;
  config.baudrate = 1000000;
  config.baudrateFD = 2000000;
  config.propdelay = 190;
  config.bus_length = 1;
  config.sample = 87.5;
  canBusFD.setRegions(64);
  canBusFD.setBaudRate(config);
  canBusFD.mailboxStatus();

  ///init values
  //pinMode(input_pin, INPUT_PULLUP);

  pinMode(KEY_PIN_01, INPUT);
  pinMode(KEY_PIN_02, INPUT);
  pinMode(KEY_PIN_03, INPUT);
  pinMode(KEY_PIN_04, INPUT);

  pinMode(LED_15, OUTPUT);
  pinMode(LED_16, OUTPUT);

  digitalWrite(LED_15, HIGH);
  digitalWrite(LED_16, HIGH);
  delay(500);

  digitalWrite(LED_15, LOW);
  digitalWrite(LED_16, LOW);


  state = START;
  num_count = 0;

  Serial.println("Init server done");
}

//----------------------------------------------------------------
void loop() {
  uint8_t pintCanFD = digitalRead(KEY_PIN_01);

  //test data to CAN Bus FD
  sendFDMsg(pintCanFD);

  uint8_t pinCANBus = digitalRead(KEY_PIN_02);

  //test data to CAN Bus
  sendCanBusMsg(pinCANBus);
}

//----------------------------------------------------------------
void canSniff(const CAN_message_t &msg) { // global callback
  Serial.print("T4: ");
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print(" OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print(" BUS "); Serial.print(msg.bus);
  Serial.print(" LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" REMOTE: "); Serial.print(msg.flags.remote);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" IDHIT: "); Serial.print(msg.idhit);

  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();

}

//----------------------------------------------------------------
void sendCanBusMsg(uint8_t input) {
  if (input == HIGH) {
    Serial.print("Writing CAN FD: ");
    CANMotorMessage msg = CANMotorMessage(MOTOR_ID);
    Serial.println(MOTOR_ID);
    Serial.print(" ");
    uint8_t colors[3] = {0, 255, 255};
    msg.addMessage(0, colors, 01111000, 01100011);
    msg.addMessage(2, colors, 01000000, 00001011);
    msg.addMessage(5, colors, 01111110, 01111111);
    msg.addMessage(6, colors, 01111110, 01111111);
    canBus.write(msg.returnCANmessage());
    Serial.println();
  }
}
//----------------------------------------------------------------
void sendFDMsg(uint8_t input) {
  if (input == HIGH) {
    Serial.print("Writing CAN FD: ");
    CANMotorMessage msg = CANMotorMessage(MOTOR_ID);
    Serial.println(MOTOR_ID);
    Serial.print(" ");
    uint8_t colors[3] = {0, 255, 255};
    msg.addMessage(0, colors, 01111000, 01100011);
    msg.addMessage(2, colors, 01000000, 00001011);
    msg.addMessage(5, colors, 01111110, 01111111);
    msg.addMessage(6, colors, 01111110, 01111111);
    canBusFD.write(msg.returnCANmessage());
    Serial.println();
  }
}

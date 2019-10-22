#include <Arduino.h>
#include <FlexCAN.h>
#include "UrbanPixel.h"

//define pins
#define LED_PIN_01 15
#define LED_PIN_02 16

#define KEY_PIN_01 20
#define KEY_PIN_02 21
#define KEY_PIN_03 22
#define KEY_PIN_04 23


#define NUM_PIXELS 8

FlexCAN CANbus(1000000);


//key
int pinkey01Cur = 0;
int pinkey01Prev = 0;

int pinkey02Cur = 0;
int pinkey02Prev = 0;

int pinkey03Cur = 0;
int pinkey03Prev = 0;

int pinkey04Cur = 0;
int pinkey04Prev = 0;


//message
static CAN_message_t msg;
int changeMSg = true;

Pixel pixels[1 + NUM_PIXELS];


// -------------------------------------------------------------
static void hexDump(uint8_t dumpLen, uint8_t *bytePtr)
{
  uint8_t hex[17] = "0123456789abcdef";
  uint8_t working;
  while (dumpLen--) {
    working = *bytePtr++;
    Serial.write(hex[working >> 4]);
    Serial.write(hex[working & 15]);
  }
  Serial.write('\r');
  Serial.write('\n');
}

// -------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  delay(2000);

  for (int i = 1; i <= NUM_PIXELS; i ++) {
    pixels[i] = Pixels(i);
  }

  for (int i = 1; i <= NUM_PIXELS; i++) {
    pixels[i].setup();
  }

  CANbus.begin();
  Serial.println(F("Starting Sending"));
}

void interpret_msg(CAN_message_t rxMsg, Pixel pixels[1 + NUM_PIXELS]) {

  int motor_id = int(rxMsg.buf[0]);
  int motor_dir = int(rxMsg.buf[1]);
  int motor_step = int(rxMsg.buf[2]);
  int motor_time_activation = int(rxMsg.buf[3]);
  int motor_enable = int(rxMsg.buf[4]);

  uint8_t interaction = rxMsg.buf[5];

  int motor_sensor0 = int(rxMsg.buf[6]);
  int motor_sensor1 = int(rxMsg.buf[7]);


}

// -------------------------------------------------------------
void loop(void)
{

  pinkey01Prev = pinkey01Cur;
  pinkey02Prev = pinkey02Cur;
  pinkey03Prev = pinkey03Cur;
  pinkey04Prev = pinkey04Cur;

  pinkey01Cur = digitalRead(KEY_PIN_01);
  pinkey02Cur = digitalRead(KEY_PIN_02);
  pinkey03Cur = digitalRead(KEY_PIN_03);
  pinkey04Cur = digitalRead(KEY_PIN_04);


  //rest
  msg.len = 8;
  msg.id = 0x222;
  changeMSg = false;

  for ( int idx = 0; idx < 8; ++idx ) {
    msg.buf[idx] = 0;
  }

  //if thre is a change send a msg
  if (pinkey01Cur != pinkey01Prev) {
    changeMSg = true;
    msg.buf[0] = char(pinkey01Cur);
    Serial.println("change key 1");
  }

  if (pinkey02Cur != pinkey02Prev) {
    changeMSg = true;
    msg.buf[1] = char(pinkey02Cur);
    Serial.println("change key 2");
  }

  if (pinkey03Cur != pinkey03Prev) {
    changeMSg = true;
    msg.buf[2] = char(pinkey03Cur);
    Serial.println("change key 3");
  }

  if (pinkey04Cur != pinkey04Prev) {
    changeMSg = true;
    msg.buf[3] = char(pinkey04Cur);
    Serial.println("change key 4");
  }


  // Check the interface to see if we need to update motors
  // Check to see if motors are about to collide with something
  // Check buttons to see if we need to move motors


  // Change the msg accordingly to send to

  //change msg
  if (changeMSg) {
    CANbus.write(msg);
    Serial.println("Sent");
  }


  if (!changeMSg) {
    //RX message
    CAN_message_t rxMsg;
    while (CANbus.available()) {

      CANbus.read(rxMsg);
      Serial.print("CAN BUS: ");
      hexDump(8, rxMsg.buf);

      digitalWrite(LED_PIN_01, int(rxMsg.buf[0]));
      digitalWrite(LED_PIN_01, int(rxMsg.buf[1]));
      digitalWrite(LED_PIN_02, int(rxMsg.buf[2]));
      digitalWrite(LED_PIN_02, int(rxMsg.buf[3]));
    }
  }
}

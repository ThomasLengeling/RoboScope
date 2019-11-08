/*
 * Server code that is meant to test the ClientBoard code 
*/

#include "CanBusParser.h"

CanBusParser * canBusParser = new CanBusParser();

#define LED_PIN_01 15
#define LED_PIN_02 16

#define KEY_PIN_01 20
#define KEY_PIN_02 21
#define KEY_PIN_03 22
#define KEY_PIN_04 23

//key
int pinkey01Cur = 0;
int pinkey02Cur = 0;
int pinkey03Cur = 0;
int pinkey04Cur = 0;

int pinkey01Prev = 0;
int pinkey02Prev = 0;
int pinkey03Prev = 0;
int pinkey04Prev = 0;

uint8_t msg[] = {0,1,0,0,0,0,0,0};

// -------------------------------------------------------------
void setup(void)
{
  Serial.begin(9600);
  delay(2000);

  Serial.println(F("Starting Sending"));
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
  
  /*
   * Msg structure
   * [0] : motorID
   * [1] : motorDir
   * [2] : motorStep
   * [3] : motorTimeActivation
   * [4] : motorEnable
   * [5] : interaction
   * [6] : motorSensor0
   * [7] : motorSensor1
  */


  // pinkey01 affects the motor direction
  if (pinkey01Cur != pinkey01Prev) {
    changeMSg = true;
    msg[1] *= -1;
    Serial.println("change key 1");
  }

  // pinkey02 increases the motor step
  if (pinkey02Cur != pinkey02Prev) {
    changeMSg = true;
    msg[2] += 1;
    Serial.println("change key 2");
  }

  // pinkey03 decreases the motor step
  if (pinkey03Cur != pinkey03Prev) {
    changeMSg = true;
    msg[2] -= 1;
    if (msg[2] <= 0) {
      msg[2] = 0;
    }
    Serial.println("change key 3");
  }

  //change msg
  if (changeMSg) {
    canBusParser->updateMsg(msg);
    canBusParser->sendMsg();
    Serial.println("Sent");
  }

  if (!changeMSg) {
    //RX message
    CAN_message_t rxMsg;
    while (CANbus.available()) {

      CANbus.read(rxMsg);
      Serial.print("CAN BUS: ");
      hexDump(8, rxMsg.buf);
    }
  }
}

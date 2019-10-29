#include <Arduino.h>
#include <FlexCAN.h>
#include "UrbanPanel.h"

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
static CAN_message_t oldRxMsg;
int changeMSg = true;

// Panel Control
int panelID = 0;
UrbanPanel urbanPanel;

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

  oldRxMsg.len = 8
  oldRxMsg.id = 0x222;

  urbanPanel = new UrbanPanel(panelID);

  urbanPanel.setup();

  CANbus.begin();
  Serial.println(F("Starting Sending"));
}

void interpretMsg(UrbanPanel urbanPanel, CAN_message_t rxMsg) {
  int motorID = int(rxMsg.buf[0]);
  int motorDir = int(rxMsg.buf[1]);
  int motorStep = int(rxMsg.buf[2]);
  int motorTimeActivation = int(rxMsg.buf[3]);
  int motorEnable = int(rxMsg.buf[4]);

  urbanPanel.moveMotor(motorID, motorDir, motorStep, motorTimeActivation, motorEnable);

  uint8_t interaction = rxMsg.buf[5];

  int motorSensor0 = int(rxMsg.buf[6]);
  int motorSensor1 = int(rxMsg.buf[7]);
}

// -------------------------------------------------------------
void loop(void)
{
  // Check the interface to see if we need to update motors and update the motors accordingly
  urbanPanel.checkInterfaceInput();

  // Check to see if motors are about to collide with something
  // Check buttons to see if we need to move motors

  //rest
  msg.len = 8;
  msg.id = 0x222;
  changeMSg = false;


  for ( int idx = 0; idx < 8; ++idx ) {
    msg.buf[idx] = 0;
  }

  //if there is a change send a msg
  if (urbanPanel.stateChanged()){
    changeMSg = true;
    // TODO: modify message
  }

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

      // Check to see if the new msg gained is different from before
      if (rxMsg == oldRxMsg) {
        break;
      }
      oldRxMsg = rxMsg;

      Serial.print("CAN BUS: ");
      hexDump(8, rxMsg.buf);

      interpretMsg(urbanPanel, rxMsg);
    }
  }
}

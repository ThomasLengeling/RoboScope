#include <FlexCAN_T4.h>
#include "teensy.h"
#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

const byte SWITCH_01_SX01 = 8; // LED connected to pin 8
const byte SWITCH_02_SX01 = 6; // LED connected to pin 9
const byte SWITCH_03_SX01 = 9; // LED connected to pin 10
const byte SWITCH_04_SX01 = 7; // LED connected to pin 11

const byte SWITCH_05_SX02 = 8; // LED connected to pin 12
const byte SWITCH_06_SX02 = 6; // LED connected to pin 13
const byte SWITCH_07_SX02 = 9; // LED connected to pin 14
const byte SWITCH_08_SX02 = 7; // LED connected to pin 15

//DOWN BUTTONS
const byte DOWN_01_SX01 = 12; // LED connected to pin 8
const byte DOWN_02_SX01 = 4; // LED connected to pin 9
const byte DOWN_03_SX01 = 15; // LED connected to pin 10
const byte DOWN_04_SX01 = 5; // LED connected to pin 11

const byte DOWN_05_SX02 = 12; // LED connected to pin 12
const byte DOWN_06_SX02 = 4; // LED connected to pin 13
const byte DOWN_07_SX02 = 15; // LED connected to pin 14
const byte DOWN_08_SX02 = 5; // LED connected to pin 15


//UP BUTTONS
const byte UP_01_SX01 = 11; // LED connected to pin 8
const byte UP_02_SX01 = 3; // LED connected to pin 9
const byte UP_03_SX01 = 14; // LED connected to pin 10
const byte UP_04_SX01 = 1; // LED connected to pin 11

const byte UP_05_SX02 = 11; // LED connected to pin 12
const byte UP_06_SX02 = 3; // LED connected to pin 13
const byte UP_07_SX02 = 14; // LED connected to pin 14
const byte UP_08_SX02 = 1; // LED connected to pin 15

//TOUCH PIN
const byte TOUCH_01_SX01 = 10; // LED connected to pin 8
const byte TOUCH_02_SX01 = 2; // LED connected to pin 9
const byte TOUCH_03_SX01 = 13; // LED connected to pin 10
const byte TOUCH_04_SX01 = 0; // LED connected to pin 11

const byte TOUCH_05_SX02 = 10; // LED connected to pin 12
const byte TOUCH_06_SX02 = 2; // LED connected to pin 13
const byte TOUCH_07_SX02 = 13; // LED connected to pin 14
const byte TOUCH_08_SX02 = 0; // LED connected to pin 15

//MUX
const byte DIP_01_SX03 = 5; // LED connected to pin 8
const byte DIP_02_SX03 = 6; // LED connected to pin 9
const byte DIP_03_SX03 = 7; // LED connected to pin 10
const byte DIP_04_SX03 = 8; // LED connected to pin 11
const byte DIP_05_SX03 = 9; // LED connected to pin 12
const byte DIP_06_SX03 = 10; // LED connected to pin 13
const byte DIP_07_SX03 = 11; // LED connected to pin 14
const byte DIP_08_SX03 = 12; // LED connected to pin 15
const byte DIP_09_SX03 = 13; // LED connected to pin 14
const byte DIP_10_SX03 = 14; // LED connected to pin 15

//NEO PIXELS PINS

const byte SX1509_ADDRESS_00 = 0x3E;  // SX1509 I2C address
SX1509 sx00;

const byte SX1509_ADDRESS_01 = 0x3F;
SX1509 sx01;

const byte SX1509_ADDRESS_10 = 0x71;
SX1509 sx02;

const byte SX1509_ADDRESS_11 = 0x70;
SX1509 sx03;


FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> FD;
Teensy teensy9 = Teensy(9);

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
  overhead();
}

void loop() {
  CANFD_message_t msg;

  if (FD.read(msg)) { 
    teensy9.read_msg(msg);
  }
}

void overhead() {
  sx01.pinMode(SWITCH_01_SX01, INPUT);
  sx01.pinMode(SWITCH_02_SX01, INPUT);
  sx01.pinMode(SWITCH_03_SX01, INPUT);
  sx01.pinMode(SWITCH_04_SX01, INPUT);

  sx01.pinMode(DOWN_01_SX01, INPUT);
  sx01.pinMode(DOWN_02_SX01, INPUT);
  sx01.pinMode(DOWN_03_SX01, INPUT);
  sx01.pinMode(DOWN_04_SX01, INPUT);

  sx01.pinMode(UP_01_SX01, INPUT);
  sx01.pinMode(UP_02_SX01, INPUT);
  sx01.pinMode(UP_03_SX01, INPUT);
  sx01.pinMode(UP_04_SX01, INPUT);

  sx01.pinMode(TOUCH_01_SX01, INPUT);
  sx01.pinMode(TOUCH_02_SX01, INPUT);
  sx01.pinMode(TOUCH_03_SX01, INPUT);
  sx01.pinMode(TOUCH_04_SX01, INPUT);

  //sx 01
  sx02.pinMode(SWITCH_05_SX02, INPUT);
  sx02.pinMode(SWITCH_06_SX02, INPUT);
  sx02.pinMode(SWITCH_07_SX02, INPUT);
  sx02.pinMode(SWITCH_08_SX02, INPUT);

  sx02.pinMode(DOWN_05_SX02, INPUT);
  sx02.pinMode(DOWN_06_SX02, INPUT);
  sx02.pinMode(DOWN_07_SX02, INPUT);
  sx02.pinMode(DOWN_08_SX02, INPUT);

  sx02.pinMode(UP_05_SX02, INPUT);
  sx02.pinMode(UP_06_SX02, INPUT);
  sx02.pinMode(UP_07_SX02, INPUT);
  sx02.pinMode(UP_08_SX02, INPUT);

  sx02.pinMode(TOUCH_05_SX02, INPUT);
  sx02.pinMode(TOUCH_06_SX02, INPUT);
  sx02.pinMode(TOUCH_07_SX02, INPUT);
  sx02.pinMode(TOUCH_08_SX02, INPUT);

  //sx 03

  sx03.pinMode(DIP_01_SX03, INPUT);
  sx03.pinMode(DIP_02_SX03, INPUT);
  sx03.pinMode(DIP_03_SX03, INPUT);
  sx03.pinMode(DIP_04_SX03, INPUT);
  sx03.pinMode(DIP_05_SX03, INPUT);
  sx03.pinMode(DIP_06_SX03, INPUT);
  sx03.pinMode(DIP_07_SX03, INPUT);
  sx03.pinMode(DIP_08_SX03, INPUT);
  sx03.pinMode(DIP_09_SX03, INPUT);
  sx03.pinMode(DIP_10_SX03, INPUT);
}

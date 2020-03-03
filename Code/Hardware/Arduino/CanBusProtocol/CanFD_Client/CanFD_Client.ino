#include <FlexCAN_T4.h>
#include "teensy.h"
#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

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

const byte SX1509_ADDRESS_00 = 0x3E;  // SX1509 I2C address
SX1509 sx00;

const byte SX1509_ADDRESS_01 = 0x3F;
SX1509 sx01;

const byte SX1509_ADDRESS_10 = 0x71;
SX1509 sx02;

const byte SX1509_ADDRESS_11 = 0x70;
SX1509 sx03;


FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_256> FD;
Teensy teensy9 = Teensy(9, sx01, sx02);

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
    CANFD_message_t return_msg = teensy9.read_msg(msg);
    FD.write(return_msg);
  }
  teensy9.motor_update();
}

void overhead() {
  if (!sx00.begin(SX1509_ADDRESS_00) ) {
    Serial.println("Failed 0");
    Serial.println(SX1509_ADDRESS_00);
  } else {
    Serial.println("Connected 0");
  }

  if (!sx03.begin(SX1509_ADDRESS_10)) {
    Serial.println("Failed sx 3");
    Serial.println(SX1509_ADDRESS_10);
  } else {
    Serial.println("Connected 3");
  }

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

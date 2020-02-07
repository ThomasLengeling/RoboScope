/*
   Client Code to run on each board. Board controls up to n type of motors

   Thomas Sanchez Lengeling
   Terry Kang

   MIT Media Lab
   City Science

*/


#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library

#include <Arduino.h>
#include "UrbanPixel.h"
#include "Debug.h"

UrbanPixel * UrbanPixel;

volatile boolean limitActivated = false;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Starting");
  delay(2000);

  // The 0th pixel
  urbanPixel = new UrbanPixel(0);

  Serial.println(F("Setting up pixel 0:"));
  urbanPixel.setup();

  Serial.println(F("Starting Sending"));

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_SWITCH), limitswitch, CHANGE);
}

// -------------------------------------------------------------
void loop(void)
{

}

void limitMove() {

  urbanPanel->stopMotorsToLimitPosition();

}

//
//https://arduino.stackexchange.com/questions/20608/pass-classs-public-function-as-an-argument-to-external-command
void limitswitch() {
  limitActivated = true;
}

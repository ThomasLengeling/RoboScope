#include <Arduino.h>


#include "BoardPins.h"
#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library


#include "StepperMotor.h"
#include "Interface.h"
#include "UrbanPixel.h"


/*
   Client Code to run on each board. Board controls up to n type of motors

   Thomas Sanchez Lengeling
   Terry Kang

   MIT Media Lab
   City Science

*/

//Interface * interface_c;
//StepperMotor * motor_c;

UrbanPixel * urbanPixel;
SX1509 sx;

const byte SX1509_ADDRESS_00 = 0x3E;

volatile boolean limitActivated = false;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Starting");
  delay(2000);

  Serial.println("Setting up Mux:");
  int muxCounter = 0;
  while (muxCounter != 3) {
    if (!sx.begin(SX1509_ADDRESS_00)) {
      Serial.println(SX1509_ADDRESS_00);
      Serial.println("Failed 00");
      muxCounter++;
    } else {
      Serial.println("Connected 00");
      break;
    }
  }

  //pushDownPin[0] = SX1509_01_SWITCH_LEDBOX;
  //pushDownPin[1] = SX1509_02_SWITCH_LEDBOX;

  //limitSwithPin[0] = SX1509_01_SWITCH_STOP;
  //limitSwithPin[1] = SX1509_02_SWITCH_STOP;

  //DIR_PIN_01
  //DIR_PIN_02

  //STEP_PIN_01
  //STEP_PIN_02

  
  // The 0th pixel
  Interface interface_c = Interface(SX1509_01_SWITCH_LEDBOX, SX1509_01_SWITCH_STOP, sx);
  StepperMotor motor_c = StepperMotor(0, GMOTOR_STEPS, DIR_PIN_01, STEP_PIN_01, GENABLE_PIN, GM0_PIN, GM1_PIN);
  urbanPixel = new UrbanPixel(0, motor_c, interface_c);

  Serial.println(F("Setting up pixel 0:"));
  urbanPixel->setup();

  Serial.println(F("Starting Sending"));

  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN_SWITCH), limitswitch, CHANGE);
}

// -------------------------------------------------------------
void loop(void)
{

}


//
//https://arduino.stackexchange.com/questions/20608/pass-classs-public-function-as-an-argument-to-external-command
void limitswitch() {
  limitActivated = true;
}

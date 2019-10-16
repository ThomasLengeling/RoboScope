#include <Arduino.h>
#include "Stepper.h"
#include "MotorPins.h"

//Motor 1
Stepper motor01(0, GMOTOR_STEPS, DIR_PIN_01, STEP_PIN_01, GSLEEP_PIN, GM0_PIN, GM1_PIN);

//Motor 2
Stepper motor02(1, GMOTOR_STEPS, DIR_PIN_02, STEP_PIN_02, GSLEEP_PIN, GM0_PIN, GM1_PIN);


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //start the motors;
  motor01.init();
  motor02.init();

  //print the motor info
  motor01.printMotorInfo();
  motor02.printMotorInfo();
}

void loop() {
  // put your main code here, to run repeatedly:

  //timer for moving up and down several motors at once

}

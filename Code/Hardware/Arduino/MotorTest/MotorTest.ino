#include <Arduino.h>
#include "Stepper.h"
#include "MotorPins.h"

//Motor 1
Stepper motor01(0, GMOTOR_STEPS, DIR_PIN_01, STEP_PIN_01, GENABLE_PIN, GM0_PIN, GM1_PIN);

//Motor 2
Stepper motor02(1, GMOTOR_STEPS, DIR_PIN_02, STEP_PIN_02, GENABLE_PIN, GM0_PIN, GM1_PIN);

//input response
char user_input;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  Serial.println("Starting");

  //start the motors;
  motor01.init();
  motor02.init();

 delay(2000);

  //print the motor info
  motor01.printMotorInfo();
  motor02.printMotorInfo();
}

void loop() {
  //timer for moving up and down several motors at once
  while (Serial.available()) {
    user_input = Serial.read();

    if (user_input == '1') {
      motor02.moveForward();
      motor01.moveForward();
      Serial.println("motor 2 forward");
      delay(1000);
    }

    if (user_input == '2') {
      motor02.moveBackward();
      motor01.moveBackward();
      Serial.println("motor 2 backward");
      delay(1000);
    }

  }
}

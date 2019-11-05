#ifndef MOTOR_PANEL_H
#define MOTOR_PANEL_H


#include <Arduino.h>

#include "StepperMotor.h"
#include "MotorPins.h"

/*
 * The Motor Panel controls the output for all the motors available to the urban panel
*/

class MotorPanel {
  public:
    int id;
    StepperMotor * motors[MOTORS_PER_PANEL];
    //constructor
    MotorPanel(int pId) {
      id = pId;

      int motor_DIR_PINS[]  = {6, 8 ,10, 15, 17, 21, 23, 25};
      int motor_STEP_PINS[] = {5, 7, 9, 14, 16, 20, 22, 24};

      for (int i = 0; i < MOTORS_PER_PANEL; i++) {
        motors[i] = new StepperMotor(i, GMOTOR_STEPS, motor_DIR_PINS[i], motor_STEP_PINS[i], GENABLE_PIN, GM0_PIN, GM1_PIN);
      }
    }

    // initialize motors
    void init() {
      for (int i = 0; i < MOTORS_PER_PANEL; i++){
        motors[i]->init();
      }
    }

    // Returns a motor based on id
    StepperMotor getMotor(int i) {
      return *motors[i];
    }

    // Prints the motor info
    void printDebugInfo() {
      for (int i = 0; i < MOTORS_PER_PANEL; i++){
        motors[i]->printMotorInfo();
      }
    }
};

#endif

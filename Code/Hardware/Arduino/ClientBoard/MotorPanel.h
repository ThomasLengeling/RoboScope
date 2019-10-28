#include <Arduino.h>

#include "StepperMotor.h"
#include "MotorPins.h"

/*
 * The Motor Panel controls the output for all the motors available to the urban panel
*/

class MotorPanel : public StepperMotor{
  public:
    int id;
    int motor_count_per_panel;

    //constructor
    MotorPanel(int p_id) {
      id = p_id;

      int motor_DIR_PINS[] = DIR_PINS;
      int motor_STEP_PINS[] = STEP_PINS;

      StepperMotor motors[MOTORS_PER_PANEL];

      for (int i = 0; i < MOTORS_PER_PANEL; i++) {
        motors[i] = new StepperMotor(i, GMOTOR_STEPS, motor_DIR_PINS[i], motor_STEP_PINS[i], GENABLE_PIN, GM0_PIN, GM1_PIN);
      }
    }

    // initialize motors
    void init() {
      for (int i = 0; i < MOTORS_PER_PANEL; i++){
        motors[i].init();
      }
    }

    // Returns a motor based on id
    StepperMotor getMotor(int i) {
      return motors[i];
    }

    // Prints the motor info
    void printDebugInfo() {
      for (int i = 0; i < MOTORS_PER_PANEL; i++){
        motors[i].printMotorInfo();
      }
    }
};

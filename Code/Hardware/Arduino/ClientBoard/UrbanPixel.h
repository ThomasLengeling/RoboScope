#include <Arduino.h>

#include "StepperMotor.h"
#include "MotorPins.h"

#include "Interface.h"
#include "InterfacePins.h"

/*
   The individual pixel unit that controls the stepper, the lights, and handles the inputs of the respective pixel
*/

class UrbanPixel : public StepperMotor, Interface {
  public:
    // ID for the pixel (also used for the motor ID)
    int id;

    //constructor
    UrbanPixel(int p_id) {
      id = p_id;

      int motor_DIR_PINS[] = DIR_PINS;
      int motor_STEP_PINS[] = STEP_PINS;

      int neo_pixel_pins[] = NEO_PIXEL_PINS;
      int push_button_pins[] = PUSH_BUTTON_PINS;
      int limit_switch_pins[] = LIMIT_SWITCH_PINS;
      int sensor_pins[] = SENSOR_PINS;

      // Initialize the stepper motor
      StepperMotor(id, GMOTOR_STEPS, motor_DIR_PINS[id], motor_STEP_PINS[id], GENABLE_PIN, GM0_PIN, GM1_PIN);
      Interface(new_pixel_pins[id], push_button_pins[id], limit_switch_pins[id]);

    }


    // initialize motors
    void setup() {
      motor.init();
      ui.init();
    }

    // Prints the motor info
    void printDebugInfo() {
      motor.printMotorInfo();
    }


};

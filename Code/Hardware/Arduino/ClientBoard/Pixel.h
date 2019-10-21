#include <Arduino.h>

#include "Stepper.h"
#include "MotorPins.h"

#include "Interface.h"
#include "InterfacePins.h"

/*
 * The individual pixel unit that controls the stepper, the lights, and handles the inputs of the respective pixel
 */

class UrbanPixel : public Stepper : public Interface{
  public:
    // ID for the pixel (also used for the motor ID)
    int id;

    //constructor
    Pixel(int p_id) {
      id = p_id;

      int motor_DIR_PINS[] = DIR_PINS;
      int motor_STEP_PINS[] = STEP_PINS;

      int neo_pixel_pins[] = NEO_PIXEL_PINS;
      int push_button_pins[] = PUSH_BUTTON_PINS;
      int limit_switch_pins[] = LIMIT_SWITCH_PINS;
      int sensor_pins[] = SENSOR_PINS;


      // Initialize the stepper motor
      Stepper motor(id, GMOTOR_STEPS, motor_DIR_PINS[id], motor_STEP_PINS[id], GENABLE_PIN, GM0_PIN, GM1_PIN);
      Interface ui(new_pixel_pins[id], push_button_pins[id], limit_switch_pins[id]);

    }

    void setup() {
      // initialize motors
      motor.init();
      ui.init();
    }

    void printDebugInfo(){

      // Prints the motor info
      motor.printMotorInfo();
    }


    

};


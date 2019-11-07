/*
   Control for DRV8880 stepper motor driver
*/
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>
#include "DRV8880.h"


class StepperMotor {
  public:

    //direction pin
    int DIR_PIN;

    //step pin
    int STEP_PIN;

    int ENABLE_PIN;

    //Microstepping control pins
    int M0_PIN;
    int M1_PIN;

    // Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
    int motorSteps;
    int rpm;

    //driver id;
    int id;

    //DRV8880 class
    DRV8880  * motor;

    //constructor
    StepperMotor(int m_id, int steps, int dir_pin, int step_pin, int sleep_pin, int m0_pin, int m1_pin) {
      id  = m_id;
      motorSteps = steps;

      //pins
      DIR_PIN   = dir_pin;
      STEP_PIN  = step_pin;
      ENABLE_PIN = sleep_pin;
      M0_PIN = m0_pin;
      M1_PIN = m1_pin;

      //init motor driver
      motor = new DRV8880(motorSteps, DIR_PIN, STEP_PIN);//, ENABLE_PIN, M0_PIN, M1_PIN);

    }

    void setRPM(int RPM) {
      rpm = RPM;
    }

    //delete pointer memory
    ~StepperMotor() {
      //delete motor;
    }

    void init() {
      motor->begin(rpm);

      // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line

      // motor->setEnableActiveState(LOW);

      motor->enable();
    }

    void stop() {
      motor->stop();
    }

    void moveForward() {
      motor->setMicrostep(1);
      motor->move(motorSteps);
    }

    void moveBackward() {
      motor->setMicrostep(1);
      motor->move(-motorSteps);
    }

    void moveForwardMicro(int step) {
      motor->setMicrostep(step);
      motor->move(step * motorSteps);
    }

    void moveBackwardMicro(int step) {
      motor->setMicrostep(step);
      motor->move(-step * motorSteps);
    }

    //print out information
    void printMotorInfo() {
      Serial.print("MOTOR id: ");
      Serial.println(id);
      Serial.print("MOTOR Steps: ");
      Serial.println(motorSteps);
      Serial.print("DIR pin: ");
      Serial.println(DIR_PIN);
      Serial.print("STEP PIN: ");
      Serial.println(DIR_PIN);
      Serial.print("SLEEP PIN: ");
      Serial.println(ENABLE_PIN);
      Serial.print("M0 PIN: ");
      Serial.println(M0_PIN);
      Serial.print("M1 PIN: ");
      Serial.println(M1_PIN);
    }

};

#endif

/*
   Control for DRV8880 stepper motor driver
*/
#ifndef STEPPER_MOTOR_H
#define STEPPER_MOTOR_H

#include <Arduino.h>
#include "BoardPins.h"
#include "DRV8880.h"
#include "Timer.h"


//---------------------------------------------------------------------------------
class StepperMotor {
  public:

    //constructor
    StepperMotor(int m_id, int steps, int dir_pin, int step_pin, int sleep_pin, int m0_pin, int m1_pin) {
      id  = m_id;
      motorSteps = steps;

      //update the pins
      DIR_PIN   = dir_pin;
      STEP_PIN  = step_pin;
      ENABLE_PIN = sleep_pin;
      M0_PIN = m0_pin;
      M1_PIN = m1_pin;

      //enable the motor
      pinMode(ENABLE_PIN, OUTPUT);
      digitalWrite(ENABLE_PIN, HIGH);
      enableMotor = true;

      //init motor driver
      motor = new DRV8880(motorSteps, DIR_PIN, STEP_PIN);// ENABLE_PIN, M0_PIN, M1_PIN);

      //limit timer
      timerBack = new Timer(500);

      //lock the state of the motor
      motorLock = false;
      stopMotor = false;

    }

    void setRPM(int RPM) {
      rpm = RPM;
    }

    //delete pointer memory
    ~StepperMotor() {
      //delete motor;
    }

    //-----------------------------------------------------------
    void init() {
      motor->setRPM(GRPM);
      motor->begin(rpm);

      // if using enable/disable on ENABLE pin (active LOW) instead of SLEEP uncomment next line
      //  motor->setEnableActiveState(LOW);
      motor->enable();
    }

    void moveUp() {
      motor->move(-motorSteps);
    }

    void startMoveUp(int steps) {
      motor->startMove(steps * -motorSteps);
    }

    void startMoveDown(int steps) {
      motor->startMove(steps * motorSteps);
    }

    unsigned getNextAction() {
      return motor->nextAction();
    }

    void stop() {
      motor->disable();
    }

    void moveDown() {
      motor->move(motorSteps);
    }

    void enable() {
      digitalWrite(ENABLE_PIN, HIGH);
      enableMotor = true;
    }
    void disable() {
      digitalWrite(ENABLE_PIN, LOW);
      enableMotor = false;
    }


    bool updateLock(unsigned long time) {
      timerBack->update(time);
      if (timerBack->isDone()) {
        timerBack->reset();
        return true;
      }
      return false;
    }

    //activate limit
    void activeLimit() {
      stopMotor = true;
      motorLock = false;
    }

    void resetlimit() {
      motorLock = true;
      stopMotor = false;
    }

    bool isMotorStop() {
      return stopMotor;
    }

    bool isMotorLock() {
      return motorLock;
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

  private:

    //direction pin
    int DIR_PIN;

    //step pin
    int STEP_PIN;

    //eanble pin
    int ENABLE_PIN;

    //Microstepping control pins
    int M0_PIN;
    int M1_PIN;

    // Motor steps per revolution. Most steppers are 200 steps or 1.8 degrees/step
    int motorSteps;
    int rpm;

    //driver id;
    int id;

    boolean enableMotor;

    //DRV8880 class
    DRV8880  * motor;

    boolean  motorLock;
    boolean stopMotor;

    Timer    * timerBack;
};

#endif

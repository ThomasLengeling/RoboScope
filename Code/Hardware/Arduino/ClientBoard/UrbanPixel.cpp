#include "UrbanPixel.h"
#include "StepperMotor.h"
#include "Interface.h"
#include "BoardPins.h"

//------------------------------------------------------------------------------
// constructor

UrbanPixel::UrbanPixel(int pixelId) {
  id = pixelId;

  int motorDirPins[]  = {DIR_PIN_01, DIR_PIN_02 , DIR_PIN_03, DIR_PIN_04, DIR_PIN_05, DIR_PIN_06, DIR_PIN_07, DIR_PIN_08};
  int motorStepPins[] = {STEP_PIN_01, STEP_PIN_02, STEP_PIN_03, STEP_PIN_04, STEP_PIN_05, STEP_PIN_06, STEP_PIN_07, STEP_PIN_08};

  motor = new StepperMotor(id, GMOTOR_STEPS, motorDirPins[id], motorStepPins[id], GENABLE_PIN, GM0_PIN, GM1_PIN);
  interface = new Interface();
}

/*
void UrbanPixel::setColor(int r, int g, int b) {
  interface->setColor(r, g, b);
}

void UrbanPixel::setSubPixelColor(int i, int r, int g, int b) {
  interface->setSubPixelColor(i, r, g, b);
}

int UrbanPixel::getPushButtonState() {
  return interface->getPushButtonState();
}

int UrbanPixel::getLimitSwitchState() {
  return interface->getLimitSwitchState();
}
*/

// timer for moving up and down the motor in parallel with others
// Also checks the limits of the motor to make sure movment is bounded
// Have this run in the main update loop
void UrbanPixel::updateMotorPositions(boolean *limitActivated) {
  if (motor->isMotorStop()) {
    motor->disable();
    Serial.println("waiting lock");

    if (!motor->isMotorLock()){
      bool lock = motor->updateLock(millis());

      if (lock) {
        motor->enable();
        motor->startMoveUp( 5 );
        motor.resetlimit();

        Serial.print(id);
        Serial.println(": lock and back");
      }
    }
  }

  unsigned waitTimeMicros = motor->getNextAction();
  if (waitTimeMicros <= 0) {
    motor->disable();
    Serial.print(id);
    Serial.println(": stop motor");
  }

  if (limitActivated) {
    interface->updateLimitState();
    if (interface->getLimitSwitchState()) {
      motor->activeLimit();
      Serial.println(id);
      Serial.println(": limit up");
    }

    if (interface->getLimitState()) {
      interface->resetLimitSwitch();
    }

    if (interface->getPushButtonState()) {
      motor->activeLimit();
      Serial.print(id);
      Serial.println(": push down");
    }

    if (interface->getPushButtonState()){
      interface->resetPushSwitch();
    }
  }
  limitActivated = false;
}


void UrbanPixel::moveUp(int steps = 10){
  motor->startMoveUp( steps );
}

void UrbanPixel::moveDown(){
  motor->startMoveDown( steps );
}

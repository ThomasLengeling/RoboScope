#include "Interface.h"

//------------------------------------------------------------------------------
// constructor
Interface::Interface(int pushPin, int limitPin, SX1509 *sx) {

  sx00 = sx;

  pushDownPin = pushPin;

  limitSwitchPin = limitPin;
}

//------------------------------------------------------------------------------
void Interface::init() {
  // TODO: neopixels (do this at the urban panel stage?)

  sx00->pinMode(pushDownPin, INPUT_PULLUP);
  sx00->pinMode(limitSwitchPin, INPUT_PULLUP);

  sx00->enableInterrupt(pushDownPin, CHANGE );
  sx00->enableInterrupt(limitSwitchPin, CHANGE );

  sx00->debounceTime(4);

  sx00->debouncePin(pushDownPin);
  sx00->debouncePin(limitSwitchPin);

  pinMode(INTERRUPT_PIN_SWITCH, INPUT_PULLUP);
}

void Interface::updateLimitState() {
  unsigned int intStatus = sx00->interruptSource();

  Serial.print("limit ");
  unsigned state = intStatus & (1 << limitSwitchPin);

  limitSwitchStatePrev = limitSwitchState;
  limitSwitchState = state;

  Serial.print(bool(state));
  Serial.print("-");
  Serial.print(limitSwitchState);
  Serial.print("-");
  Serial.print(limitSwitchStatePrev);
  Serial.println(" ");

  Serial.print("push ");

  state = intStatus & (1 << pushDownPin);

  pushDownStatePrev = pushDownState;
  pushDownState = state;

  Serial.print(bool(state));
  Serial.print("-");
  Serial.print(pushDownState);
  Serial.print("-");
  Serial.print(pushDownStatePrev);
  Serial.println(" ");

  Serial.println(" ");

}

bool Interface::getLimitSwitchState() {
  if ( !limitSwitchStatePrev && limitSwitchState) {
    return true;
  }
  return false;
}

bool Interface::getLimitState() {
  if ( limitSwitchStatePrev && limitSwitchState) {
    return true;
  }
  return false;
}

void Interface::updatePushState() {
  unsigned int intStatus = sx00->interruptSource();
}

bool Interface::getPushDownState() {
  if (!pushDownStatePrev && pushDownState) {
    return true;
  }
  return false;
}

bool Interface::getPushState() {
  if (pushDownStatePrev && pushDownState) {
    return true;
  }
  return false;
}

int Interface::getPushCurrentState() {
  return sx00->digitalRead(pushDownPin);
}

int Interface::getLimitCurrentState() {
  return sx00->digitalRead(limitSwitchPin);
}

void Interface::resetLimitSwitch() {
  limitSwitchStatePrev = false;
  limitSwitchState = false;
}

void Interface::resetPushDown() {
  pushDownStatePrev = false;
  pushDownState = false;
}

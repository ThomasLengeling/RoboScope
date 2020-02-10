#include "Interface.h"

//------------------------------------------------------------------------------
// constructor
Interface::Interface(int pushPin, int limitPin, SX1509 *sx) {

  sx00 = *sx;

  pushDownPin = pushPin;
  pushSwitchState = false;
  pushSwitchStatePrev = false;

  limitSwitchPin = limitPin;
  limitSwitchState = false;
  limitSwitchStatePrev = false;
}

//------------------------------------------------------------------------------
void Interface::init() {
  // TODO: neopixels (do this at the urban panel stage?)

  Serial.println("Setting up Mux:");

  sx00->pinMode(pushDownPin, INPUT_PULLUP);
  sx00->pinMode(limitSwitchPin, INPUT_PULLUP);

  sx00->enableInterrupt(pushDownPin, CHANGE );
  sx00->enableInterrupt(limitSwithPin, CHANGE );

  sx00->debounceTime(4);

  sx00->debouncePin(pushDownPin);
  sx00->debouncePin(limitSwithPin);

  pinMode(INTERRUPT_PIN_SWITCH, INPUT_PULLUP);
}

void Interface::setColor(int r, int g, int b){
  // TODO
}

void Interface::setSubPixelColor(int i, int r, int g, int b) {
  // TODO
}

bool Interface::getLimitSwitchState() {
  if ( !limitSwitchStatePrev && limitSwitchState)
    return true;
  return false;
}

bool Interface::getLimitState() {
  if ( limitSwitchStatePrev && limitSwitchState)
    return true;
  return false;
}

void resetLimitSwitch() {
  limitSwitchStatePrev = false;
  limitSwitchState = false;
}

bool Interface::getPushSwitchState() {
  if ( !pushSwitchStatePrev && pushSwitchState)
    return true;
  return false;
}

bool Interface::getPushState() {
  if ( pushSwitchStatePrev && pushSwitchState)
    return true;
  return false;
}

void resetPushSwitch() {
  pushSwitchStatePrev = false;
  pushSwitchState = false;
}

void Interface::updateLimitState() {
  unsigned int intStatus = sx00.interruptSource();
  // For debugging handiness, print the intStatus variable.
  // Each bit in intStatus represents a single SX1509 IO.
  // Serial.println("intStatus = " + String(intStatus, BIN));

  // If the bit corresponding to out button IO generated
  // the input:
  Serial.print("limit ");

  unsigned state = intStatus & (1 << limitSwitchPin);

  limitSwitchStatePrev = limitSwitchState;
  limitSwitchState = state;

  Serial.print(bool(state));
  Serial.print("-");
  Serial.print(limitSwitchState);
  Serial.print("-");
  Serial.print(limitSwitchStatePrev);
  Serial.print(" ");

  Serial.println();

  Serial.print("push ");
  unsigned state = intStatus & (1 << pushDownPin);

  pushSwitchStatePrev = pushSwitchState;
  pushSwitchState = state;

  Serial.print(bool(state));
  Serial.print("-");
  Serial.print(pushSwitchState);
  Serial.print("-");
  Serial.print(pushSwitchStatePrev);
  Serial.print(" ");

  Serial.println();

}

void Interface::updatePushState() {
  unsigned int intStatus = sx00.interruptSource();
}

int Interface::getPushCurrentState() {
  return sx00->digitialRead(pushDownPin);
}

int Interface::getLimitCurrentState() {
  return sx00->digitalRead(limitSwitchPin);
}

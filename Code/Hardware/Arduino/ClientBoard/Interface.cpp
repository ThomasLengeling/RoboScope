#include "Interface.h"

//------------------------------------------------------------------------------
// constructor
Interface::Interface(int pushPin, int limitPin, SX1509 *sx) {

  sx00 = *sx;

  pushDownPin = pushPin;
  limitSwitchPin = limitPin;

}

//------------------------------------------------------------------------------
void Interface::init() {
  // TODO: neopixels (do this at the urban panel stage?)

  Serial.prinln("Setting up Mux:");

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


int Interface::getPushButtonState() {
  return sx00->digitialRead(pushDownPin);
}

int Interface::getLimitSwitchState() {
  return sx00->digitalRead(limitSwitchPin);
}

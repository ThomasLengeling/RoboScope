/*
   The class that controls the interactive elements of the pixel
   This is where the buttons and sensors are declared
*/
#ifndef INTERFACE_H
#define INTERFACE_H

#include <Arduino.h>
#include <SparkFunSX1509.h>
#include "BoardPins.h"
//#include <Adafruit_NeoPixel.h>

class Interface {
  public:
    // constructor
    Interface(int pushPin, int limitPin, SX1509 sx);

    void init();

    bool getLimitSwitchState();

    bool getLimitState();

    void resetLimitSwitch();

    bool getPushSwitchState();

    bool getPushState();

    void resetPushSwitch();

    void updateLimitState();

    void updatePushState();

    int getPushCurrentState();

    int getLimitCurrentState();

  private:

    int pushDownPin;
    bool pushSwitchState;
    bool pushSwitchStatePrev;

    int limitSwitchPin;
    bool limitSwitchState;
    bool limitSwitchStatePrev;

    SX1509 * sx00;
};

#endif

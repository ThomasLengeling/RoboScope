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
    Interface(int pushPin, int limitPin, SX1509 *sx);

    void init();

    void updateLimitState();

    bool getLimitSwitchState();

    bool getLimitState();

    void updatePushState();

    bool getPushDownState();

    bool getPushState();

    int getPushCurrentState();

    int getLimitCurrentState();

    void resetLimitSwitch();

    void resetPushDown();

  private:

    int pushDownPin;
    int limitSwitchPin;

    bool limitSwitchStatePrev;
    bool limitSwitchState;

    bool pushDownStatePrev;
    bool pushDownState;


    SX1509 * sx00;
};

#endif

/*
   Interface Panel Code

*/
#ifndef INTERFACE_PANEL_H
#define INTERFACE_PANEL_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "InterfaceDefines.h"
#include "BoardPins.h"

class InterfacePanel {
  public:

    // constructor
    InterfacePanel(int pId);

    int getUrbanPixelCount();

    void init();

    void setColorAll(int r, int g, int b);

    // Sets the color on a per urban pixel basis
    void setColorUrbanPixel(int urbanPixelId, int r, int g, int b);

    // Sets the color on a sub urban pixel basis
    // Each urban pixel may be made up of multiple neopixels, this function gives control over them individually
    void setColorSubUrbanPixel(int urbanPixelId, int subPixel, int r, int g, int b);

    int getInterfaceButtonState(int i);

    int getLimitSwitchState(int i);

  private:
    int id;

    // interface button pins
    int interfacePins[NUM_URBAN_PIXELS];

    // limit switch pin high
    int limitPinsH[NUM_URBAN_PIXELS];

    Adafruit_NeoPixel * neopixels;
};

#endif

/*
 * Interface Panel Code
 * 
 */
#ifndef INTERFACE_PANEL_H
#define INTERFACE_PANEL_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "InterfaceDefines.h"
#include "BoardPins.h"

class InterfacePanel {
  public:
    int id;

    // interface button pins
    int interfacePins[NUM_URBAN_PIXELS] = {3};

    // limit switch pin high
    int limitPinsH[NUM_URBAN_PIXELS] = {2};

    Adafruit_NeoPixel * neopixels;

    // constructor
    InterfacePanel(int pId) {
      id = pId;
      neopixels = new Adafruit_NeoPixel(NUM_URBAN_PIXELS * PIXELS_PER_URBAN_PIXEL, NEO_PIXEL_PIN, NEO_GRBW + NEO_KHZ800);
    }

    int getUrbanPixelCount() {
      return NUM_URBAN_PIXELS;
    }

    void init() {
      neopixels->begin();
      for (int i = 0; i < NUM_URBAN_PIXELS; i++){
        pinMode(interfacePins[i], INPUT);
        pinMode(limitPinsH[i], INPUT);
      }
    }

    void setColorAll(int r, int g, int b) {
      for (int i = 0; i < NUM_URBAN_PIXELS * PIXELS_PER_URBAN_PIXEL; i ++) {
        neopixels->setPixelColor(i, neopixels->Color(r, g, b));
      }
      neopixels->show();
    }

    // Sets the color on a per urban pixel basis
    void setColorUrbanPixel(int urbanPixelId, int r, int g, int b) {
      int startIndex = urbanPixelId * PIXELS_PER_URBAN_PIXEL;
      for (int i = startIndex; i < startIndex + PIXELS_PER_URBAN_PIXEL; i++) {
        neopixels->setPixelColor(i, neopixels->Color(r, g, b));
      }
      neopixels->show();
    }

    // Sets the color on a sub urban pixel basis
    // Each urban pixel may be made up of multiple neopixels, this function gives control over them individually
    void setColorSubUrbanPixel(int urbanPixelId, int subPixel, int r, int g, int b){
      int i = (urbanPixelId * PIXELS_PER_URBAN_PIXEL) + subPixel;

      neopixels->setPixelColor(i, neopixels->Color(r, g, b));
      neopixels->show();
    }

    int getInterfaceButtonState(int i) {
      return digitalRead(interfacePins[i]);
    }

    int getLimitSwitchState(int i) {
      return digitalRead(limitPinsH[i]);
    }

};

#endif

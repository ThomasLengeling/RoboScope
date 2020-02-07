/*
   The class that controls the interactive elements of the pixel
   This is where the buttons and sensors are declared
*/

#ifndef INTERFACE_H
#define INTERFACE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

class Interface {
  public:
    // constructor
    Interface(Adafruit_NeoPixel neopixels);

}

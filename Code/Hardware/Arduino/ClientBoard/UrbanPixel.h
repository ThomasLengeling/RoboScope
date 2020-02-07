/*
   The class that controls the functions of the Urban Pixel
   Can handel the inputs and outputs of each pixel
   Holds the interaction code
*/
#ifndef URBAN_PIXEL_H
#define URBAN_PIXEL_H

#include <Arduino.h>

#include "StepperMotor.h"
#include "Interface.h"

class UrbanPixel {
  public:
    // constructor
    UrbanPixel(int pixelId);

    // Moves the pixel up
    void moveUp();

    // Moves the pixel down
    void moveDown();

    // Stops the movement of the pixel
    void stop();


  private:
    int id;

}

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
#include "BoardPins.h"

class UrbanPixel {
  public:
    // constructor
    UrbanPixel(int pixelId, StepperMotor *motor_c, Interface *interface_c);

    void setup();

    void updateMotorPosition(bool *limitActivated);

    // Moves the pixel up
    void moveUp(int steps);

    // Moves the pixel down
    void moveDown(int steps);

    // Stops the movement of the pixel
    void stopMotor();



  private:
    int id;

    StepperMotor * motor;
    Interface * interface;
};

#endif

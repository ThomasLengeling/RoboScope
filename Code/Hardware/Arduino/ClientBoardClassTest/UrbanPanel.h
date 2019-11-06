#ifndef URBAN_PANEL_H
#define URBAN_PANEL_H

#include <Arduino.h>

#include "MotorPanel.h"
#include "InterfacePanel.h"

/*
 * The class that controls the overall functions of the Urban Panel (a panel made up of Urban Pixels)
 * Can handle the output and inputs of each urban pixel in the panel
   The individual pixel unit that controls the stepper, the lights, and handles the inputs of the respective pixel
*/

class UrbanPanel {
  public:
    // ID for the pixel (also used for the motor ID)
    int id;
    
    MotorPanel * motorPanel;
    InterfacePanel * interfacePanel;
    
    // variable that keeps track of whether or not elements in the urban panel changed (i.e. motor moved, buttons pressed, etc)
    bool stateChanged = false;

    //constructor
    UrbanPanel(int panelId) {
      id = panelId;

      motorPanel = new MotorPanel(id);
      interfacePanel = new InterfacePanel(id);
    }

    // returns the state of interface (sensor output, all button states, LEDs)
    int getInterfaceState() {
      return 0;
    }

    // returns the state of all the motors
    int getMotorState() {
      return 0;
    }

    // resets the state status variable
    void resetState(){
        stateChanged = false;
    }

    // returns true if the interface has been changed
    bool getStateChanged(){
        return stateChanged;
    }

    // Iteratively goes through all interface push buttons to see if any are activated
    // Modifies motor output as necessary
    void checkInterfaceInput() {
      for (int i = 0; i < interfacePanel->getUrbanPixelCount(); i++){
        if(interfacePanel->getInterfaceButtonState(i)){
           moveMotorDown(i);
           stateChanged = true;
        }
      }
    }

    void setUrbanPixelColor(int i, int r, int g, int b){
      interfacePanel->setColorUrbanPixel(i, r, g, b);
    }


    // TODO: Check to make sure the specified directions are the directions for the motor
    // TODO: Check to see if the stepper motor stops moving up when button is pressed
    // Moves the specified urban pixel up
    void moveMotorUp(int i){
      if (!interfacePanel->getInterfaceButtonState(i)) {
        motorPanel->getMotor(i).moveForward();
      } else {
        motorPanel->getMotor(i).stop();
      }
    }

    // Moves the specified urban pixel down
    void moveMotorDown(int i){
      if (!interfacePanel->getLimitSwitchState(i)) {
        motorPanel->getMotor(i).moveBackward();
      } else {
        motorPanel->getMotor(i).stop();
      }
    }

    void moveMotor(int motorID,int motorDir,int motorStep,int motorTimeActivation,int motorEnable){
      if (motorDir == 1){
          moveMotorUpMicro(motorID, motorStep, motorTimeActivation, motorEnable);
      } else {
          moveMotorDownMicro(motorID, motorStep, motorTimeActivation, motorEnable);
      }
    }

    void moveMotorUpMicro(int motorID,int motorStep,int motorTimeActivation,int motorEnable){
      if (!interfacePanel->getInterfaceButtonState(motorID)){
        motorPanel->getMotor(motorID).moveForwardMicro(motorStep);
      }
    }
    
    void moveMotorDownMicro(int motorID,int motorStep,int motorTimeActivation,int motorEnable){
      if (!interfacePanel->getLimitSwitchState(motorID)){
        motorPanel->getMotor(motorID).moveBackwardMicro(motorStep);
      }
    }

    MotorPanel getMotorPanel(){
      return *motorPanel;
    }

    InterfacePanel getInterfacePanel(){
      return *interfacePanel;
    }

    // initialize motors
    void setup() {
      motorPanel->init();
      interfacePanel->init();
    }
};

#endif

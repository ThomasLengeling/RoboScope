#include "UrbanPanel.h"


//------------------------------------------------------------------------------
//constructor
UrbanPanel::UrbanPanel(int panelId) {
  id = panelId;

  stateChanged = false;

  motorPanel = new MotorPanel(id);
  interfacePanel = new InterfacePanel(id);
}


//------------------------------------------------------------------------------
// returns the state of interface (sensor output, all button states, LEDs)
int UrbanPanel::getInterfaceState() {
  return 0;
}

//------------------------------------------------------------------------------
// returns the state of all the motors
int UrbanPanel::getMotorState() {
  return 0;
}

//------------------------------------------------------------------------------
// resets the state status variable
void UrbanPanel::resetState() {
  stateChanged = false;
}

//------------------------------------------------------------------------------
// returns true if the interface has been changed
bool UrbanPanel::getStateChanged() {
  return stateChanged;
}

//------------------------------------------------------------------------------
// Iteratively goes through all interface push buttons to see if any are activated
// Modifies motor output as necessary
void UrbanPanel::checkInterfaceInput() {
  for (int i = 0; i < interfacePanel->getUrbanPixelCount(); i++) {
    if (interfacePanel->getInterfaceButtonState(i)) {
      moveMotorDown(i);
      stateChanged = true;
    }
  }
}


//------------------------------------------------------------------------------
void UrbanPanel::setUrbanPixelColor(int i, int r, int g, int b) {
  interfacePanel->setColorUrbanPixel(i, r, g, b);
}


//------------------------------------------------------------------------------
// TODO: Check to make sure the specified directions are the directions for the motor
// TODO: Check to see if the stepper motor stops moving up when button is pressed
// Moves the specified urban pixel up
void UrbanPanel::moveMotorUp(int i) {
  if (!interfacePanel->getInterfaceButtonState(i)) {
    motorPanel->getMotor(i).moveForward();
  } else {
    motorPanel->getMotor(i).stop();
  }
}

//------------------------------------------------------------------------------
// Moves the specified urban pixel down
void UrbanPanel::moveMotorDown(int i) {
  if (!interfacePanel->getLimitSwitchState(i)) {
    motorPanel->getMotor(i).moveBackward();
  } else {
    motorPanel->getMotor(i).stop();
  }
}


//------------------------------------------------------------------------------
void UrbanPanel::moveMotor(int motorID, int motorDir, int motorStep, int motorTimeActivation, int motorEnable) {
  if (motorDir == 1) {
    moveMotorUpMicro(motorID, motorStep, motorTimeActivation, motorEnable);
  } else {
    moveMotorDownMicro(motorID, motorStep, motorTimeActivation, motorEnable);
  }
}


//------------------------------------------------------------------------------
void UrbanPanel::moveMotorUpMicro(int motorID, int motorStep, int motorTimeActivation, int motorEnable) {
  if (!interfacePanel->getInterfaceButtonState(motorID)) {
    motorPanel->getMotor(motorID).moveForwardMicro(motorStep);
  }
}


//------------------------------------------------------------------------------
void UrbanPanel::moveMotorDownMicro(int motorID, int motorStep, int motorTimeActivation, int motorEnable) {
  if (!interfacePanel->getLimitSwitchState(motorID)) {
    motorPanel->getMotor(motorID).moveBackwardMicro(motorStep);
  }
}

//------------------------------------------------------------------------------
MotorPanel UrbanPanel::getMotorPanel() {
  return *motorPanel;
}


//------------------------------------------------------------------------------
InterfacePanel UrbanPanel::getInterfacePanel() {
  return *interfacePanel;
}

//------------------------------------------------------------------------------
// initialize motors
void UrbanPanel::setup() {
  motorPanel->init();
  interfacePanel->init();
}

#include <Arduino.h>

#include "MotorPanel.h"
#include "InterfacePanel.h"

/*
 * The class that controls the overall functions of the Urban Panel (a panel made up of Urban Pixels)
 * Can handle the output and inputs of each urban pixel in the panel
   The individual pixel unit that controls the stepper, the lights, and handles the inputs of the respective pixel
*/

class UrbanPanel : public MotorPanel, InterfacePanel {
  public:
    // ID for the pixel (also used for the motor ID)
    int id;

    //constructor
    UrbanPanel(int panel_id) {
      id = panel_id;

      MotorPanel motorPanel = new MotorPanel(id);
      Interface interfacePanel = new InterfacePanel(id);
    }

    // Iteratively goes through all interface push buttons to see if any are activated
    // Modifies motor output as necessary
    void checkInterfaceInput() {
      for (int i = 0; i < interfacePanel.getUrbanPixelCount(); i++){
        if(interfacePanel.getInterfaceButtonState(i)){
           moveUrbanPixelDown(i);
        }
      }
    }



    // TODO: Check to make sure the specified directions are the directions for the motor
    // TODO: Check to see if the stepper motor stops moving up when button is pressed
    // Moves the specified urban pixel up
    void moveUrbanPixelUp(int i){
      if (!interfacePanel.getInterfaceButtonState(i)) {
        motorPanel.getMotor(i).moveForward();
      } else {
        motorPanel.getMotor(i).stop();
      }
    }

    // Moves the specified urban pixel down
    void moveUrbanPixelDown(int i){
      if (!interfacePanel.getLimitSwitchState(i)) {
        motorPanel.getMotor(i).moveBackward();
      } else {
        motorPanel.getMotor(i).stop();
      }
    }

    MotorPanel getMotorPanel(){
      return motorPanel;
    }

    InterfacePanel getInterfacePanel(){
      return interfacePanel;
    }

    // initialize motors
    void setup() {
      motorPanel.init();
      interfacePanel.init();
    }
};

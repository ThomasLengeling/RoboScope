/*
 * Client Code to run on each board. Board controls up to n type of motors
 * 
 * Thomas Sanchez Lengeling
 * Terry Kang
 * 
 * MIT Media Lab
 * City Science
 * 
 */
#include <Arduino.h>
#include "UrbanPanel.h"
#include "CanBusParser.h"


// Panel Control
int panelID = 0;

UrbanPanel * urbanPanel = new UrbanPanel(panelID);
CanBusParser * canBusParser = new CanBusParser();

void setup(void)
{
  Serial.begin(9600);
  delay(2000);


  urbanPanel->setup();

  Serial.println(F("Starting Sending"));
}

// -------------------------------------------------------------
void loop(void)
{
  // Checks to see if certain buttons are being pressed to move the motor (represents user interaction)
  urbanPanel->checkInterfaceInput();

  // if there is a change to the state send a message
  if (urbanPanel->getStateChange()){
    uint8_t message[8];

    // Temporary just to emphasize that there was a change to the system
    for (int i = 0; i < 8; i++){
      message[i] = 1;
    }
    canBusParser->updateMsg(message);
    canBusParser->sendMsg();
  }

  canBusParser->waitforMsg();

  uint8_t msg[8];
  canBusParser->getRxMsg(msg);

  urbanPanel->interpretMsg(msg);
}

#include <Arduino.h>
#include "UrbanPanel.h"


// Panel Control
int panelID = 0;

UrbanPanel urbanPanel = new UrbanPanel(panelID);

void setup(void)
{
  Serial.begin(9600);
  delay(2000);



  urbanPanel.setup();

  Serial.println(F("Starting Sending"));
}

// -------------------------------------------------------------
void loop(void)
{
  // Checks to see if certain buttons are being pressed to move the motor (represents user interaction)
  urbanPanel.checkInterfaceInput();
}

#include "InterfacePanel.h"

//---------------------------------------------------------------------------
// constructor
InterfacePanel::InterfacePanel(int pId) {
  id = pId;
  neopixels = new Adafruit_NeoPixel(NUM_URBAN_PIXELS * PIXELS_PER_URBAN_PIXEL, NEO_PIXEL_PIN, NEO_GRBW + NEO_KHZ800);

  // interface button pins
  for (int i = 0; i < NUM_URBAN_PIXELS; i++) {
    interfacePins[i]  = 3;
  }
  for (int i = 0; i < NUM_URBAN_PIXELS; i++) {
    limitPinsH[i]  = 2;
  }
  
}


//---------------------------------------------------------------------------
int InterfacePanel::getUrbanPixelCount() {
  return NUM_URBAN_PIXELS;
}

//---------------------------------------------------------------------------
void InterfacePanel::init() {
  neopixels->begin();
  for (int i = 0; i < NUM_URBAN_PIXELS; i++) {
    pinMode(interfacePins[i], INPUT);
    pinMode(limitPinsH[i], INPUT);
  }
}

//---------------------------------------------------------------------------
void InterfacePanel::setColorAll(int r, int g, int b) {
  for (int i = 0; i < NUM_URBAN_PIXELS * PIXELS_PER_URBAN_PIXEL; i ++) {
    neopixels->setPixelColor(i, neopixels->Color(r, g, b));
  }
  neopixels->show();
}

//---------------------------------------------------------------------------
// Sets the color on a per urban pixel basis
void InterfacePanel::setColorUrbanPixel(int urbanPixelId, int r, int g, int b) {
  int startIndex = urbanPixelId * PIXELS_PER_URBAN_PIXEL;
  for (int i = startIndex; i < startIndex + PIXELS_PER_URBAN_PIXEL; i++) {
    neopixels->setPixelColor(i, neopixels->Color(r, g, b));
  }
  neopixels->show();
}


//---------------------------------------------------------------------------
// Sets the color on a sub urban pixel basis
// Each urban pixel may be made up of multiple neopixels, this function gives control over them individually
void InterfacePanel::setColorSubUrbanPixel(int urbanPixelId, int subPixel, int r, int g, int b) {
  int i = (urbanPixelId * PIXELS_PER_URBAN_PIXEL) + subPixel;

  neopixels->setPixelColor(i, neopixels->Color(r, g, b));
  neopixels->show();
}


//---------------------------------------------------------------------------
int InterfacePanel::getInterfaceButtonState(int i) {
  return digitalRead(interfacePins[i]);
}


//---------------------------------------------------------------------------
int InterfacePanel::getLimitSwitchState(int i) {
  return digitalRead(limitPinsH[i]);
}

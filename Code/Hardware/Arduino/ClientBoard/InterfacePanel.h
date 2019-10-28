#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "InterfacePins.h"

class InterfacePanel {
  public:
    int id;

    Adafruit_NeoPixel * neopixels;

    InterfacePanel(int p_id) {
      id = p_id;

      // interface button pins
      int interfacePins[] = PUSH_BUTTON_PINS;

      // limit switch pin high
      int limitPinH[] = LIMIT_SWITCH_PINS;

      Adafruit_NeoPixel neopixels = new Adafruit_NeoPixel(NUM_URBAN_PIXELS * PIXELS_PER_URBAN_PIXEL, NEO_PIXEL_PIN, NEO_GRB + NEO_KHZ800);
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
      int startIndex = urbanPixelId * PIXELS_PER_URBAN_PIXEL
      for (int i = startIndex; i < startIndex + PIXELS_PER_URBAN_PIXEL; i++) {
        neopixels->setPixelColor(i, neopixel->Color(r, g, b));
      }
      neopixels->show();
    }

    // Sets the color on a sub urban pixel basis
    // Each urban pixel may be made up of multiple neopixels, this function gives control over them individually
    void setColorSubUrbanPixel(int urban_pixel_id, int subPixel, int r, int g, int b){
      int i = (urbanPixelId * PIXELS_PER_URBAN_PIXEL) + subPixel;

      neopixels->setPixelColor(i, neopixel->Color(r, g, b));
      neopixels->show();
    }

    int getInterfaceButtonState(int i) {
      return digitalRead(interfacePins[i]);
    }

    int getLimitSwitchState(int i) {
      return digitalRead(limitPinsH[i]);
    }

};

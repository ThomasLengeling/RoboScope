#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 1

//TODO: SEE COMMENTS IN INTERFACEP PINS .h

class Interface {
  public:
    // led pin
    int ledPin;

    // interface button pin
    int interfacePin;

    // limit switch pin high
    int limitPinH;

    Adafruit_NeoPixel * neopixels;

    Interface(int led_pin, int interface_button, int limit_switch) {
      ledPin = led_pin;
      interfacePin = interface_button;
      limitPinH = limit_switch;

      neopixels = new Adafruit_NeoPixel(NUM_PIXELS, ledPin, NEO_GRB + NEO_KHZ800);
    }

    void init() {
      neopixels->begin();
      pinMode(interfacePin, INPUT);
      pinMode(limitPinH, INPUT);
    }

    void setColorAll(int r, int g, int b) {
      for (int i = 0; i < NUM_PIXELS; i ++) {
        neopixels->setPixelColor(i, neopixels->Color(r, g, b));
      }
      neopixels->show();
    }

    int getInterfaceButtonState() {
      return digitalRead(interfacePin);
    }

    int getLimitSwitchState() {
      return digitalRead(limitPinH);
    }

};

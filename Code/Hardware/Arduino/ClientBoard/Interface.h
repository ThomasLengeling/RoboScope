#include <Arduino.h>
#include <Adafruit_Neopixel.h>

#define NUM_PIXELS 1

//TODO: SEE COMMENTS IN INTERFACEP PINS .h

class Interface {
  public:
    // led pin
    int l_pin;

    // interface button pin
    int i_pin;

    // limit switch pin
    int l_pin;

    
    Interface(int led_pin, int interface_button, int limit_switch) {
      neopixels = Adafruit_Neopixel(NUM_PIXELS, led_pin, NEO_GRB + NEO_KHZ800);
    }

    void init() {
      neopixels.begin();
      pinMode(i_pin, INPUT);
      pinMode(l_pin, INPUT);
    }

    void setColorAll(int r, int g, int b) {
      for (int i = 0; i < NUM_PIXELS; i ++) {
        neopixels.setPixelColor(i, neopixels.Color(r, g, b));
      }
      neopixels.show();
    }

    int getInterfaceButtonState() {
      return digitalRead(i_pin);
    }

    int getLimitSwitchState() {
      return digitalRead(l_pin);
    }

}

#include <FlexCAN_T4.h>
#include "motor.h"
#include <Adafruit_NeoPixel.h>

#define PIN 6 
#define NUMPIXELS 2 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRBW + NEO_KHZ800);
FlexCAN_T4FD<CAN3, RX_SIZE_256, TX_SIZE_16> FD;
Motor motor = Motor(9);
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels
uint8_t color[3] = {0}; 
void setup(void) {
  Serial.begin(115200);
  delay(500);
  FD.begin();
  CANFD_timings_t config;
  config.clock = CLK_24MHz;
  config.baudrate = 1000000;
  config.baudrateFD = 2000000;
  config.propdelay = 190;
  config.bus_length = 1;
  config.sample = 87.5;
  FD.setRegions(64);
  FD.setBaudRate(config);
  FD.mailboxStatus();
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
}

void loop() {
  CANFD_message_t msg;
  bool writeMsg = motor.updateInteraction();
  if (writeMsg) {
    FD.write(motor.write_msg());
  }
  if (FD.read(msg)) { 
    motor.read_msg(color, msg);
    FD.write(motor.write_msg());
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(color[0], color[1], color[2], 100));
    pixels.show();   // Send the updated pixel colors to the hardware.
    delay(DELAYVAL);
  }
}

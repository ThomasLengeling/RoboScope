#include <Adafruit_NeoPixel.h>
#include <SparkFunSX1509.h> // Include SX1509 library
#include <Wire.h> // Include the I2C library (required)

uint16_t convertFrom8To16(uint8_t dataFirst, uint8_t dataSecond) {
    uint16_t dataBoth;
    dataBoth = (dataFirst << 8) | dataSecond;
    return dataBoth;
}

uint8_t* convertFrom16To8(uint16_t dataAll, uint8_t* rgb) {
    rgb[0] = dataAll >> 8;
    rgb[1] = dataAll & 0x00FF;
    return rgb;
}

class Motor {
  public:
    Motor(int id, byte neo_pin, byte switch_pin, byte down_pin, byte up_pin, byte touch_pin);
    uint8_t* read_msg(uint8_t* color, CANFD_message_t msg);
    void setLED();
    uint8_t* returnColor(uint8_t* colors);
    void update_sx(SX1509 sx);
    void msg_update(uint16_t color, uint8_t steps, uint8_t interaction);
    bool led_switch_handle();
    bool limit_switch_handle();
    uint8_t* return_state();
  private:
    byte NUMPIXELS;
    int id;
    byte switch_pin;
    byte down_pin;
    byte up_pin;
    byte touch_pin;
    
    uint8_t colors[3]= {0};
    uint8_t steps =0;
    uint8_t interaction=0;

    uint8_t limit_switch_state =0;
    uint8_t LED_switch_state =0;
    void setcolor(uint16_t color);
    Adafruit_NeoPixel pixel;
    SX1509 sx;
};

Motor::Motor(int id, byte neo_pin, byte switch_pin, byte down_pin, byte up_pin, byte touch_pin) {
   this->id = id;
   this->switch_pin = switch_pin;
   this->down_pin = down_pin;
   this->up_pin= up_pin;
   this->touch_pin= touch_pin;
   this->NUMPIXELS =4;
   this->pixel = Adafruit_NeoPixel(this->NUMPIXELS, neo_pin, NEO_GRBW + NEO_KHZ800);
   this->pixel.begin();
   this->pixel.clear();
   for (int j = 0; j < this->NUMPIXELS; j++) {
    this->pixel.setPixelColor(j, this->pixel.Color(255, 0, 0));
   }
   this->pixel.show();
}

void Motor::update_sx(SX1509 sx) {
  this->sx = sx;
  this->sx.pinMode(this->switch_pin, INPUT);
  this->sx.pinMode(this->down_pin, INPUT);
  this->sx.pinMode(this->up_pin, INPUT);
  this->sx.pinMode(this->touch_pin, INPUT);
}

void Motor::msg_update(uint16_t color, uint8_t steps, uint8_t interaction) {
  this->setcolor(color);
  this->steps = steps;
  this->interaction = interaction;
}

bool Motor::led_switch_handle() {
  bool change = false;
  if (this->sx.digitalRead(this->down_pin)==HIGH) {
    this->colors[0] = random(0, 255);
    this->colors[1] = random(0, 255);
    this->colors[2] = random(0, 255);
    for (int j = 0; j < this->NUMPIXELS; j++) {
      this->pixel.setPixelColor(j, this->pixel.Color(this->colors[0], this->colors[1], this->colors[2])); // Moderately bright green color.
    }
    this->pixel.show();
    change = true;
    this->LED_switch_state=3;
  }
  return change;
}

bool Motor::limit_switch_handle() {
  bool change = false;
  if (this->sx.digitalRead(this->switch_pin)==HIGH) {
    this->limit_switch_state=4;
    change = true;
  }
  return change;
}

uint8_t* Motor::return_state() {  
  this->interaction = this->LED_switch_state+this->limit_switch_state;
  uint16_t two_color = (((this->colors[0] & 0b11111000)<<8) + ((this->colors[1] & 0b11111100)<<3)+(this->colors[2]>>3));
  uint8_t rgb[2]= {0};
  convertFrom16To8(two_color, rgb);
  uint8_t msg[4] = {rgb[0],rgb[1], this->steps, this->interaction}; 
  return msg;
}

void Motor::setcolor(uint16_t color) {
  this->colors[0] = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
  this->colors[1] = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
  this->colors[2] = (((color & 0x1F) * 527) + 23) >> 6;
  for (int j = 0; j < this->NUMPIXELS; j++) {
    this->pixel.setPixelColor(j, this->pixel.Color(this->colors[0], this->colors[1], this->colors[2]));
  }
  this->pixel.show();
}

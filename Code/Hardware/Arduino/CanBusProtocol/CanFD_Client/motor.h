#include <Adafruit_NeoPixel.h>

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

uint8_t* toBits(uint8_t input, unsigned char* bit_list) {
  unsigned char bytes = (char*)input;// Read from file
  unsigned char mask = 1; // Bit mask
  int i, j = 7;
  for ( i = 0; i < 8; i++,j--,mask = 1) {
    bit_list[i] =( bytes & (mask<<=j))  != NULL;
  }
  return bit_list;
}

class Motor {
  public:
    Motor(int id, byte neo_pin);
    uint8_t* read_msg(uint8_t* color, CANFD_message_t msg);
    void setLED();
    uint8_t* returnColor(uint8_t* colors);
    void update(uint16_t color, uint8_t steps, uint8_t interaction);
  private:
    byte NUMPIXELS;
    int id;
    uint8_t colors[3]= {0};
    uint8_t steps =0;
    uint8_t interaction=0;
    void setcolor(uint16_t color);
    Adafruit_NeoPixel pixel;
};

Motor::Motor(int id, byte neo_pin) {
   this->id = id;
   this->NUMPIXELS =4;
   this->pixel = Adafruit_NeoPixel(this->NUMPIXELS, neo_pin, NEO_GRBW + NEO_KHZ800);
   this->pixel.begin();
   this->pixel.clear();
   for (int j = 0; j < this->NUMPIXELS; j++) {
    this->pixel.setPixelColor(j, this->pixel.Color(255, 0, 0));
   }
   this->pixel.show();
}


void Motor::update(uint16_t color, uint8_t steps, uint8_t interaction) {
  this->setcolor(color);
  this->steps = steps;
  this->interaction = interaction;
}

void Motor::setcolor(uint16_t color) {
  this->colors[0] = ((((color >> 11) & 0x1F) * 527) + 23) >> 6;
  this->colors[1] = ((((color >> 5) & 0x3F) * 259) + 33) >> 6;
  this->colors[2] = (((color & 0x1F) * 527) + 23) >> 6;
  Serial.println(" ");
  Serial.print("Motor: "); Serial.println(this->id);
  Serial.println(this->colors[2]);
  for (int j = 0; j < this->NUMPIXELS; j++) {
    this->pixel.setPixelColor(j, this->pixel.Color(this->colors[0], this->colors[1], this->colors[2]));
  }
  this->pixel.show();
}

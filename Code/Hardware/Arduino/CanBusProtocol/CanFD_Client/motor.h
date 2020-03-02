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
    int down_initial;
    int up_initial;
    const int BUTTON_TIMEOUT=500;
    Motor(int board_des);
    uint8_t* read_msg(uint8_t* color, CANFD_message_t msg);
    void setLED();
    uint8_t* returnColor(uint8_t* colors);
    CANFD_message_t write_msg();
    bool Motor::updateInteraction();
  private:
    int local_name;
    int index;
    int state;
    uint16_t color;
    uint8_t steps;
    uint8_t interaction;
    bool button_state;
    int button_count=0;
    void Motor::setInteraction(uint8_t button1);
};

Motor::Motor(int board_des) {
   this->local_name = board_des;
   this->index = board_des*4;
   pinMode(13,OUTPUT);
   pinMode(5, INPUT_PULLUP);
   pinMode(4, INPUT_PULLUP);
   this->state = HIGH;
   this->button_state = 0;
   digitalWrite(13,state);
}

uint8_t* Motor::read_msg(uint8_t* colors, CANFD_message_t msg) {
  if (msg.id-1 <= this->local_name && msg.id+15>this->local_name) {
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print("  TS: "); Serial.println(msg.timestamp);
    for (int i = this->index; i<this->index+4; i++) {
      Serial.print(msg.buf[i]); Serial.print(" "); 
    }
    Serial.println(" ");
    this->color = convertFrom8To16(msg.buf[this->index],msg.buf[this->index+1]);
    this->steps = msg.buf[this->index+2];
    this->interaction = msg.buf[this->index+3];
    this->setLED();
    return this->returnColor(colors);
  }
}

bool Motor::updateInteraction() {
  uint8_t button1 = digitalRead(5);
  bool writeMsg = false;
  switch(this->button_state){
    case 0:    
      if (button_count!=0) {
        Serial.println(button1);
        this->setInteraction(button1);
        writeMsg= true;
        button_count=0;
      }
      if (button1==0){
        down_initial = millis();
        this->button_state = 1;
      }
      break; //don't forget break statements
    case 1:
      Serial.println(this->button_state);
      if (millis()-down_initial > 10) {
        if (button1==1) {
          up_initial = millis();
          this->button_state = 2;
        } else {
          this->setInteraction(button1);
          writeMsg= true;
        }
      }
      break;
    case 2:
      if (millis()-up_initial > 20 && button1==0) {
        down_initial = millis();
        this->button_state = 1;
        button_count+=1;
      } else {
        this->button_state = 0;
        button_count+=1;
      }
      break;
  }
  return writeMsg;
}
void Motor::setInteraction(uint8_t button1) {
  unsigned char bit_list[8]; 
  toBits(this->interaction, bit_list);
  bit_list[6]=button1;
  byte b = 0;
  for (int i=0; i<8; i++) {
    if (bit_list[i]) {
      b+=pow(2,7-i);
    }
  }
  this->interaction = b;
}
void Motor::setLED() {
  if (this->state==HIGH) {
    this->state=LOW;
  } else {
    this->state=HIGH;
  }
  digitalWrite(13,this->state);
}

uint8_t* Motor::returnColor(uint8_t* colors) {
  colors[0] = ((((this->color >> 11) & 0x1F) * 527) + 23) >> 6;
  colors[1] = ((((this->color >> 5) & 0x3F) * 259) + 33) >> 6;
  colors[2] = (((this->color & 0x1F) * 527) + 23) >> 6;
 
  return colors;
}

CANFD_message_t Motor::write_msg() {
  CANFD_message_t msg;
  uint8_t rgb[2]= {0};
  convertFrom16To8(this->color, rgb);
  msg.id = 0xFFFFFFFF;
  msg.len=5;
  msg.buf[0]=this->local_name;
  msg.buf[1]=rgb[0];
  msg.buf[2]=rgb[1];
  msg.buf[3]=this->steps;
  msg.buf[4]=this->interaction;
  return msg;
}

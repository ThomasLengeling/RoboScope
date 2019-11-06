#include "CanBusParser.h"


//--------------------------------------------------
CanBusParser::CanBusParser() {
  canBus = new FlexCAN(SPPED_BUS);

  txMsg.len = 8;

}

//--------------------------------------------------
int CanBusParser::hexDump(uint8_t dumpLen, uint8_t *bytePtr){
  uint8_t hex[17] = "0123456789abcdef";
  uint8_t working;
  while (dumpLen--) {
    working = *bytePtr++;
    Serial.write(hex[working >> 4]);
    Serial.write(hex[working & 15]);

  }
  Serial.write('\r');
  Serial.write('\n');
}

//--------------------------------------------------
void CanBusParser::waitforMsg() {
  while (canBus->available()) {
    canBus->read(rxMsg);
  }
}

//--------------------------------------------------
void CanBusParser::sendMsg() {

}

//--------------------------------------------------
void CanBusParser::updatMsg() {

}

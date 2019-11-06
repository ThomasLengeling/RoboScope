/*
class that manages serial communication using the Can Bus protocol.
*/

#pragma once

#include "ofMain.h"

//baurate of the serial
#define baurate 57600

//memory
class CanSerial;
typedef std::shared_ptr<CanSerial> CanSerialRef;

class CanSerial{

public:

  //setup serial
  CanSerial(){
    serial.setup(mSerialId, baurate);
  }

  //delete serial
  ~CanSerial(){

  }

  //create memory
  static CanSerialRef create() {
      return std::make_shared<CanSerial>();
  }

  //send msg
  void printSerialDevice(){
    	serial.listDevices();
  }

  //set Id
  void setId(int serial){
    mSerialId = serial;
  }

  //send can Msg Protocol
  void sendCanMsg(){

  }

  //send simple msg
  void sendMsg(){

  }

private:
  int         mSerialId;
  ofSerial	  mSerial;
  bool        mSerialMessage;

  std::string mMsg;

};

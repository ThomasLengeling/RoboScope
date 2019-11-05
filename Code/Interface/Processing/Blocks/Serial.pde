import processing.serial.*;

Serial canPort01; 

int bauRate = 9600;

/*
Seril manager
*/

void setupSerial() {

  //print serials
  printArray(Serial.list());

  String portName = Serial.list()[0];
  canPort01 = new Serial(this, portName, bauRate);
}

//send test Msg
void sendTestMsg() {
  
}

/*
Matrix with height
Matrix with color
*/



//send can Msg
void sendCanMsg(){
  //write array of bytes[]
  //
 // canPort01.write();
}

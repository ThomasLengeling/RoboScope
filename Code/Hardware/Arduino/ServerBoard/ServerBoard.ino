/*
   Server code that is meant to test the ClientBoard code
*/

#include "CanBusParser.h"

//Pins inputs
#define LED_PIN_01    15
#define LED_PIN_02    16

#define KEY_PIN_01    20
#define KEY_PIN_02    21
#define KEY_PIN_03    22
#define KEY_PIN_04    23

#define MATRIX_SIZE   12 * 8

CanBusParser * canBusParser;

//key
int pinkey01Cur = 0;
int pinkey02Cur = 0;
int pinkey03Cur = 0;
int pinkey04Cur = 0;

int pinkey01Prev = 0;
int pinkey02Prev = 0;
int pinkey03Prev = 0;
int pinkey04Prev = 0;

uint8_t msg[] = {0, 1, 0, 0, 0, 0, 0, 0};

/*
 * Input msg : uint8_t -> [0 - 255]
 * 
 *             uint8_t -> 0 0 0 0 0 0 0 0 0
 *        
 *             Additional uint8_t for the type of information
 *             
 *             1 -> heights
 *             2 -> color
 *             3 -> sensor values
 *             
 *            [0] : motorID
 *            [1] : motorDir
 *            [2] : motorStep
 *            [3] : motorTimeActivation
 *            [4] : motorEnable
 *            [5] : color
 *            [6] : motorSensor0
 *            [7] : motorSensor1
 */
uint8_t msgSerial[MATRIX_SIZE + 1];

// -------------------------------------------------------------
void setup(void)
{
  Serial.begin(SERIAL_BAU);
  Serial.print("Beging Serial Port: ");
  Serial.println(SERIAL_BAU);

  canBusParser = new CanBusParser();
  delay(5000);

  //LED
  pinMode(LED_PIN_01, OUTPUT);
  pinMode(LED_PIN_02, OUTPUT);

  //Key input
  pinMode(KEY_PIN_01, INPUT);
  pinMode(KEY_PIN_02, INPUT);
  pinMode(KEY_PIN_03, INPUT);
  pinMode(KEY_PIN_04, INPUT);


  Serial.println(F("Starting Sending"));
}

// -------------------------------------------------------------
void loop(void)
{

  //update MSG
  parseInput();

  //TX MSG
  if (canBusParser->isActiveMsg()) {
    canBusParser->updateMsg(msg);
    canBusParser->sendMsg();
    Serial.println("Sent");
  }

  //RX MSG
  if (!canBusParser->isActiveMsg()) {
    canBusParser->readMsg();

  }

}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.

  TODO: Manage a better input routine, such as getting initial values from the server app
        Default size of the matrix
        Default speed
        Default input data
*/
void serialEvent() {
  while (Serial.available()) {
    //copy input msg,
    Serial.readBytes(msgSerial, MATRIX_SIZE);
    

  }
}

// -------------------------------------------------------------
void parseInput() {
  pinkey01Prev = pinkey01Cur;
  pinkey02Prev = pinkey02Cur;
  pinkey03Prev = pinkey03Cur;
  pinkey04Prev = pinkey04Cur;

  pinkey01Cur = digitalRead(KEY_PIN_01);
  pinkey02Cur = digitalRead(KEY_PIN_02);
  pinkey03Cur = digitalRead(KEY_PIN_03);
  pinkey04Cur = digitalRead(KEY_PIN_04);

  // pinkey01 affects the motor direction
  if (pinkey01Cur != pinkey01Prev) {
    canBusParser->activateMsg();
    Serial.println("change key 1");
  }

  // pinkey02 increases the motor step
  if (pinkey02Cur != pinkey02Prev) {
    canBusParser->activateMsg();
    Serial.println("change key 2");
  }

  // pinkey03 decreases the motor step
  if (pinkey03Cur != pinkey03Prev) {
    canBusParser->activateMsg();
    Serial.println("change key 3");
  }

  // pinkey04
  if (pinkey04Cur != pinkey04Prev) {
    canBusParser->activateMsg();
    Serial.println("change key 3");
  }
}

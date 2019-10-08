#include <Metro.h>
#include <FlexCAN.h>


Metro sysTimer = Metro(1);// milliseconds
FlexCAN CANbus(500000);
static CAN_message_t msg;

#define LED_PIN_01 15
#define LED_PIN_02 16

#define KEY_PIN_01 20
#define KEY_PIN_02 21
#define KEY_PIN_03 22
#define KEY_PIN_04 23


void setup() {

 CANbus.begin();
  Serial.begin(9600);
 
  //LED
  pinMode(LED_PIN_01, OUTPUT);
  pinMode(LED_PIN_02, OUTPUT);

  pinMode(KEY_PIN_01, INPUT);
  pinMode(KEY_PIN_02, INPUT);
  pinMode(KEY_PIN_03, INPUT);
  pinMode(KEY_PIN_04, INPUT);

  digitalWrite(LED_PIN_01, HIGH);
  digitalWrite(LED_PIN_02, HIGH);
  delay(2000);

  digitalWrite(LED_PIN_01, LOW);
  digitalWrite(LED_PIN_02, LOW);

  msg.buf[0]= 1;
  msg.len = 1;
  msg.timeout=100;
  msg.id = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  int pinkey01 = digitalRead(KEY_PIN_01);
  int pinkey02 = digitalRead(KEY_PIN_02);
  int pinkey03 = digitalRead(KEY_PIN_03);
  int pinkey04 = digitalRead(KEY_PIN_04);

  digitalWrite(LED_PIN_01, pinkey01);
  digitalWrite(LED_PIN_01, pinkey02);

  digitalWrite(LED_PIN_02, pinkey03);
  digitalWrite(LED_PIN_02, pinkey04);
  
  int x = CANbus.write(msg);
  Serial.write(x+48);

  delay(50);

}

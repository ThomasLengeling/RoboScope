/*************************************************************
  digitalWrite.ino
  SparkFun SX1509 I/O Expander Example: digital out (digitalWrite)
  Jim Lindblom @ SparkFun Electronics
  Original Creation Date: September 21, 2015
  https://github.com/sparkfun/SparkFun_SX1509_Arduino_Library

  This simple example demonstrates the SX1509's digital output
  functionality. Attach an LED to SX1509 IO 15, or just look at
  it with a multimeter. We're gonna blink it!

  Hardware Hookup:
	SX1509 Breakout ------ Arduino -------- Breadboard
	      GND -------------- GND
	      3V3 -------------- 3.3V
		  SDA ------------ SDA (A4)
		  SCL ------------ SCL (A5)
		  15 -------------------------------- LED+
		                                 LED- -/\/\/\- GND
                                                330

  Development environment specifics:
	IDE: Arduino 1.6.5
	Hardware Platform: Arduino Uno
	SX1509 Breakout Version: v2.0

  This code is beerware; if you see me (or any other SparkFun
  employee) at the local, and you've found our code helpful,
  please buy us a round!

  Distributed as-is; no warranty is given.
*************************************************************/

#include <Wire.h> // Include the I2C library (required)
#include <SparkFunSX1509.h> // Include SX1509 library
#include <Adafruit_NeoPixel.h>
#include "Type4067Mux.h"

//DEBUG LED NEO PIXEL
#define NEO_DEBUG      2

// SX1509 pin definitions:
const byte SX1509_LED_PIN = 15; // LED connected to pin 15


const byte SX1509_01_SWITCH = 15; // LED connected to pin 8
const byte SX1509_02_SWITCH = 14; // LED connected to pin 9
const byte SX1509_03_SWITCH = 13; // LED connected to pin 10
const byte SX1509_04_SWITCH = 12; // LED connected to pin 11
const byte SX1509_05_SWITCH = 11; // LED connected to pin 12
const byte SX1509_06_SWITCH = 10; // LED connected to pin 13
const byte SX1509_07_SWITCH = 9; // LED connected to pin 14
const byte SX1509_08_SWITCH = 8; // LED connected to pin 15

const byte SX1509_01_SWITCH_LED = 7;
const byte SX1509_02_SWITCH_LED = 6;
const byte SX1509_03_SWITCH_LED = 5;
const byte SX1509_04_SWITCH_LED = 4;
const byte SX1509_05_SWITCH_LED = 3;
const byte SX1509_06_SWITCH_LED = 2;
const byte SX1509_07_SWITCH_LED = 1;
const byte SX1509_08_SWITCH_LED = 0;

const byte SX1509_01_01_SWITCH_LED = 12;
const byte SX1509_01_02_SWITCH_LED = 14;

const byte SX1509_02_01_SWITCH_LED = 0;

const byte SX1509_03_08_SWITCH_LED = 15;
const byte SX1509_03_07_SWITCH_LED = 13;

const byte SX1509_03_01_SWITCH_LED = 1;

int colorMode = 0;
int prevColorMode = 0;

bool  colorEnable = false;


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      8

//Pixels
Adafruit_NeoPixel * pixels;

// SX1509 I2C address (set by ADDR1 and ADDR0 (00 by default):
const byte SX1509_ADDRESS_00 = 0x3E;  // SX1509 I2C address
SX1509 sx00; // Create an SX1509 object to be used throughout


const byte SX1509_ADDRESS_01 = 0x3F;   // SX1509 I2C address
SX1509 sx01; // Create an SX1509 object to be used throughout


const byte SX1509_ADDRESS_11 = 0x71;
SX1509 sx02;

const byte SX1509_ADDRESS_10 = 0x70;
SX1509 sx03;

Type4067Mux * mux;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(3000);

  Serial.begin(9600);
  //digitalWrite(13, LOW);

  Serial.println("SX1509:");

  if (!sx00.begin(SX1509_ADDRESS_00) )
  {
    Serial.println(SX1509_ADDRESS_00);
    Serial.println("Failed 00");
    while (1) ; // If we fail to communicate, loop forever.
  } else {
    Serial.println("Connected 00");
  }
/*
  if (!sx02.begin(SX1509_ADDRESS_11) )
  {
    Serial.println(SX1509_ADDRESS_11);
    Serial.println("Failed 02");
    while (1) ; // If we fail to communicate, loop forever.
  } else {
    Serial.println("Connected 02");
  }
/*
  // Call io.begin(<address>) to initialize the SX1509. If it
  // successfully communicates, it'll return 1.

  int count = 0;
  if (!sx01.begin(SX1509_ADDRESS_01))
  {
    Serial.println(SX1509_ADDRESS_01);
    Serial.println("Failed sx 01");
  } else {
    Serial.println("Connected 01");
  }

*/
  delay(2000);
  digitalWrite(13, LOW);

  // Call io.pinMode(<pin>, <mode>) to set an SX1509 pin as
  // an output:
  
  sx00.pinMode(SX1509_01_SWITCH, INPUT);
  sx00.pinMode(SX1509_02_SWITCH, INPUT);
  sx00.pinMode(SX1509_03_SWITCH, INPUT);
  sx00.pinMode(SX1509_04_SWITCH, INPUT);

  sx00.pinMode(SX1509_05_SWITCH, INPUT);
  sx00.pinMode(SX1509_06_SWITCH, INPUT);
  sx00.pinMode(SX1509_07_SWITCH, INPUT);
  sx00.pinMode(SX1509_08_SWITCH, INPUT);

  sx00.pinMode(SX1509_01_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_02_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_03_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_04_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_05_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_06_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_07_SWITCH_LED, INPUT);
  sx00.pinMode(SX1509_08_SWITCH_LED, INPUT);


  //sx01.pinMode(SX1509_01_01_SWITCH_LED, INPUT);
  //sx01.pinMode(SX1509_01_02_SWITCH_LED, INPUT);
  //sx02.pinMode(SX1509_02_01_SWITCH_LED, INPUT);


  //sx03.pinMode(SX1509_03_08_SWITCH_LED, INPUT);
  //sx03.pinMode(SX1509_03_07_SWITCH_LED, INPUT);
  //sx03.pinMode(SX1509_03_01_SWITCH_LED, INPUT);

  //mux = new Type4067Mux(8, INPUT, DIGITAL, 0, 2, 4, 6);
  // mux->signalPin(3, INPUT, DIGITAL);


  pixels = new Adafruit_NeoPixel(NUMPIXELS, NEO_DEBUG, NEO_GRBW + NEO_KHZ800);
  pixels->begin();
  pixels->clear();

}

void loop()
{
  /*
    byte data;
    for (byte i = 0; i < 16; ++i) {
      // Reads from channel i and returns HIGH or LOW.
      data = mux->read(i);
      delayMicroseconds(50);

      Serial.print("Push button at channel ");
      Serial.print(i);
      Serial.print(" is ");
      if (data == HIGH) {
        Serial.println("not pressed");
      } else if (data == LOW) {
        Serial.println("pressed");
      }
    }
    Serial.println();

    if (sx03.digitalRead(SX1509_03_08_SWITCH_LED) == HIGH) {
      Serial.println("pressed 8 button sx03");
    }

    if (sx03.digitalRead(SX1509_03_07_SWITCH_LED) == HIGH) {
      Serial.println("pressed 7 button sx03");
    }
    if (sx03.digitalRead(SX1509_03_01_SWITCH_LED) == HIGH) {
      Serial.println("pressed 1 button sx03");
    }
  */

  
/*
  if (sx02.digitalRead(SX1509_02_01_SWITCH_LED) == HIGH) {
   // Serial.println("pressed 1 button sx02");
  }

  if (sx01.digitalRead(SX1509_01_01_SWITCH_LED) == HIGH) {
  //  Serial.println("pressed 1 button sx01");
  }

  if (sx01.digitalRead(SX1509_01_02_SWITCH_LED) == HIGH) {
  //  Serial.println("pressed 2 LED sx01");
  }
*/
  //update the previous
  prevColorMode = colorMode;

  if (sx00.digitalRead(SX1509_01_SWITCH_LED) == HIGH) {
    Serial.println("pressed 1 LED");
    colorMode = 1;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_02_SWITCH_LED) == HIGH) {
    Serial.println("pressed 2 LED");
    colorMode = 2;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_03_SWITCH_LED) == HIGH) {
    Serial.println("pressed 3 LED");
    colorMode = 3;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_04_SWITCH_LED) == HIGH) {
    Serial.println("pressed 4 LED");
    colorMode = 4;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_05_SWITCH_LED) == HIGH) {
    Serial.println("pressed 5 LED");
    colorMode = 5;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_06_SWITCH_LED) == HIGH) {
    Serial.println("pressed 6 LED");
    colorMode = 6;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_07_SWITCH_LED) == HIGH) {
    Serial.println("pressed 7 LED");
    colorMode = 7;
    colorEnable = true;
  } 
  if (sx00.digitalRead(SX1509_08_SWITCH_LED) == HIGH) {
    Serial.println("pressed 8 LED");
    colorMode = 8;
    colorEnable = true;
  }


  if (sx00.digitalRead(SX1509_01_SWITCH) == HIGH) {
    Serial.println("pressed 1");
  }
  if (sx00.digitalRead(SX1509_02_SWITCH) == HIGH) {
    Serial.println("pressed 2");
  }
  if (sx00.digitalRead(SX1509_03_SWITCH) == HIGH) {
    Serial.println("pressed 3");
  }
  if (sx00.digitalRead(SX1509_04_SWITCH) == HIGH) {
    Serial.println("pressed 4");
  }
  if (sx00.digitalRead(SX1509_05_SWITCH) == HIGH) {
    Serial.println("pressed 5");
  }
  if (sx00.digitalRead(SX1509_06_SWITCH) == HIGH) {
    Serial.println("pressed 6");
  }
  if (sx00.digitalRead(SX1509_07_SWITCH) == HIGH) {
    Serial.println("pressed 7");
  }
  if (sx00.digitalRead(SX1509_08_SWITCH) == HIGH) {
    Serial.println("pressed 8");
  }


/*
  switch (colorMode) {
    case 0:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 0, 0, 255)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;
    case 1:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(255, 0, 0, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 2:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 255, 0, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 3:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 0, 255, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 4:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 255, 255, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 5:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(255, 255, 0, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 6:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(255, 0, 255, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 7:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 0, 0, 0)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;

    case 8:
      for (int i = 0; i < NUMPIXELS; i++) {
        pixels->setPixelColor(i, pixels->Color(0, 0, 0, 255)); // Moderately bright green color.
      }
      // This sends the updated pixel color to the hardware.
      pixels->show();
      break;
  }
*/
}

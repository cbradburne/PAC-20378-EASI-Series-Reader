/*
  PAC code RFID Reader (PAC ONEPROX GS3-MT)
  DipSwitches 1 - on
              2 - off
              3 - on
              4 - on
              5 - off

  For Arduino Leonardo 32u4 boards (Pro Micro) for keyboard HUD mode

  Use:
  pin 7 for LED
  pin 8 for Sig
  Gnd to Gnd
*/

#include <elapsedMillis.h>
#include <Keyboard.h>
elapsedMillis timeElapsed;
elapsedMillis timeElapsedLED;
elapsedMillis LEDflash;

const int LEDpin = 7;
unsigned int interval = 2000;
unsigned int intervalLED = 250;
bool firstSet = false;
bool firstDone = false;
bool secondDone = false;
bool thirdDone = false;
byte variable1[100];
byte variable2[100];
byte variable3[100];
byte variable4[100];
int index = 0;
String fullCode1 = "";
String fullCode2 = "";
String fullCode3 = "";
String fullCode4 = "";
String firstTest = "";
int counter = 0;

void setup()
{
  Serial.begin(9600); //9600
  while (!Serial) {
    ;
  }
  Serial1.begin(9600); //9600
  Keyboard.begin();
  pinMode(LEDpin, OUTPUT);
  digitalWrite(LEDpin, HIGH);
}

void loop()
{
  if (!firstDone) {
    if (Serial1.available() > 0) {
      byte b = Serial1.read();
      variable1[index++] = b;
      firstTest = String(variable1[index - 1], HEX);
      firstTest.toUpperCase();
      if (firstTest == "FE" && !firstSet) {
        firstSet = true;
      }
      else if (firstSet) {
        counter++;
        if (counter == 17) {
          firstDone = true;
          firstSet = false;
          firstTest = "";
          counter = 0;
          index = 0;
        }
      }
      else {
        index = 0;
      }
    }
  }

  if (firstDone && !secondDone) {
    if (Serial1.available() > 0) {
      byte b = Serial1.read();
      variable2[index++] = b;
      firstTest = String(variable2[index - 1], HEX);
      firstTest.toUpperCase();

      if (firstTest == "FE" && !firstSet) {
        firstSet = true;
      }
      else if (firstSet) {
        counter++;
        if (counter == 17) {
          secondDone = true;
          firstSet = false;
          firstTest = "";
          counter = 0;
          index = 0;
        }
      }
      else {
        index = 0;
      }
    }
  }

  

  if (firstDone && secondDone && !thirdDone) {
    if (Serial1.available() > 0) {
      byte b = Serial1.read();
      variable3[index++] = b;
      firstTest = String(variable3[index - 1], HEX);
      firstTest.toUpperCase();

      if (firstTest == "FE" && !firstSet) {
        firstSet = true;
      }
      else if (firstSet) {
        counter++;
        if (counter == 17) {
          thirdDone = true;
          firstSet = false;
          firstTest = "";
          counter = 0;
          index = 0;
        }
      }
      else {
        index = 0;
      }
    }
  }


  if (firstDone && secondDone && thirdDone) {
    if (Serial1.available() > 0) {
      byte b = Serial1.read();
      variable4[index++] = b;
      firstTest = String(variable4[index - 1], HEX);
      firstTest.toUpperCase();
      if (firstTest == "FE" && !firstSet) {
        firstSet = true;
      }
      else if (firstSet) {
        counter++;
        if (counter == 17) {
          Serial1.end();
          firstSet = false;
          firstTest = "";
          counter = 0;
          index = 0;
          doCompare();
        }
      }
      else {
        index = 0;
      }
    }
  }
}

void doCompare() {
  
  for (uint8_t i = 0; i < 17; i++) {
    if (variable1[i] < 16) fullCode1 += "0";
    fullCode1 += String(variable1[i], HEX);
    fullCode1.toUpperCase();
  }

  for (uint8_t i = 0; i < 17; i++) {
    if (variable2[i] < 16) fullCode2 += "0";
    fullCode2 += String(variable2[i], HEX);
    fullCode2.toUpperCase();
  }

  for (uint8_t i = 0; i < 17; i++) {
    if (variable3[i] < 16) fullCode3 += "0";
    fullCode3 += String(variable3[i], HEX);
    fullCode3.toUpperCase();
  }

  for (uint8_t i = 0; i < 17; i++) {
    if (variable4[i] < 16) fullCode4 += "0";
    fullCode4 += String(variable4[i], HEX);
    fullCode4.toUpperCase();
  }
  /*
  Serial.print("1 - ");
  Serial.println(fullCode1);
  Serial.print("2 - ");
  Serial.println(fullCode2);
  Serial.print("3 - ");
  Serial.println(fullCode3);
  Serial.print("4 - ");
  Serial.println(fullCode4);
  */

  if (fullCode2 == fullCode3 && fullCode3 == fullCode4) {
    //Serial.println("SUCCESS");
    //Serial.println(fullCode2);
    Keyboard.println(fullCode2);
    delay(3000);
  }
 
  Serial1.begin(9600);
  
  fullCode1 = "";
  fullCode2 = "";
  fullCode3 = "";
  fullCode4 = "";
  firstDone = false;
  secondDone = false;
  thirdDone = false;
}

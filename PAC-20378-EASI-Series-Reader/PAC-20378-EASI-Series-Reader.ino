/*
  PAC Easi Series 20378 reader for EasiKey 1000
  Arduino Leonardo 32u4 3.3v board (Pro Micro) for keyboard HUD mode

  Use:
  RX for Sig
  Gnd to Gnd
  12k resistor between VCC (3.3v) and RX pin
*/

#include <elapsedMillis.h>
#include <Keyboard.h>
elapsedMillis timeElapsed;

unsigned int interval = 2000;
bool firstSet = false;
bool secondSet = false;
bool thirdSet = false;
bool fourthSet = false;
bool firstDone = false;
bool secondDone = false;
bool thirdDone = false;
bool DEBUG = false;
byte variable1[100];
byte variable2[100];
byte variable3[100];
byte variable4[100];
int index = 0;
String fullCode1 = "";
String fullCode2 = "";
String fullCode3 = "";
String fullCode4 = "";
String readTest = "";
int counter = 0;

void setup()
{
  if (DEBUG) {
    Serial.begin(9600); //9600
    while (!Serial) {
      ;
    }
  }
  Serial1.begin(9600); //9600
  Keyboard.begin();
}

void loop()
{
  if (!firstDone) {
    if (Serial1.available() > 0) {
      variable1[index] = Serial1.read();
      readTest = String(variable1[index++], HEX);

      if (readTest == "fe" && !firstSet) {
        firstSet = true;
      }
      else if (readTest == "9e" && firstSet && !secondSet) {
        secondSet = true;
      }
      else if (readTest == "78" && firstSet && secondSet && !thirdSet) {
        thirdSet = true;
      }
      else if (firstSet && secondSet && thirdSet) {
        counter++;
        if (counter == 14) {
          firstDone = true;
          firstSet = false;
          secondSet = false;
          thirdSet = false;
          readTest = "";
          counter = 0;
          index = 0;
        }
      }
      else {
        index = 0;
        firstSet = false;
        secondSet = false;
        thirdSet = false;
      }
    }
  }

  if (firstDone && !secondDone) {
    if (Serial1.available() > 0) {
      variable2[index] = Serial1.read();
      readTest = String(variable2[index++], HEX);

      if (readTest == "fe" && !firstSet) {
        firstSet = true;
      }
      else if (readTest == "9e" && firstSet && !secondSet) {
        secondSet = true;
      }
      else if (readTest == "78" && firstSet && secondSet && !thirdSet) {
        thirdSet = true;
      }
      else if (firstSet && secondSet && thirdSet) {
        counter++;
        if (counter == 14) {
          secondDone = true;
          firstSet = false;
          secondSet = false;
          thirdSet = false;
          readTest = "";
          counter = 0;
          index = 0;
        }
      }
      else {
        index = 0;
        firstSet = false;
        secondSet = false;
        thirdSet = false;
      }
    }
  }

  if (firstDone && secondDone && !thirdDone) {
    if (Serial1.available() > 0) {
      variable3[index] = Serial1.read();
      readTest = String(variable3[index++], HEX);

      if (readTest == "fe" && !firstSet) {
        firstSet = true;
      }
      else if (readTest == "9e" && firstSet && !secondSet) {
        secondSet = true;
      }
      else if (readTest == "78" && firstSet && secondSet && !thirdSet) {
        thirdSet = true;
      }
      else if (firstSet && secondSet && thirdSet) {
        counter++;
        if (counter == 14) {
          thirdDone = true;
          firstSet = false;
          secondSet = false;
          thirdSet = false;
          readTest = "";
          counter = 0;
          index = 0;
        }
      }
      else {
        index = 0;
        firstSet = false;
        secondSet = false;
        thirdSet = false;
      }
    }
  }

  if (firstDone && secondDone && thirdDone) {
    if (Serial1.available() > 0) {
      variable4[index] = Serial1.read();
      readTest = String(variable4[index++], HEX);

      if (readTest == "fe" && !firstSet) {
        firstSet = true;
      }
      else if (readTest == "9e" && firstSet && !secondSet) {
        secondSet = true;
      }
      else if (readTest == "78" && firstSet && secondSet && !thirdSet) {
        thirdSet = true;
      }
      else if (firstSet && secondSet && thirdSet) {
        counter++;
        if (counter == 14) {
          Serial1.end();
          firstSet = false;
          secondSet = false;
          thirdSet = false;
          readTest = "";
          counter = 0;
          index = 0;
          doCompare();
        }
      }
      else {
        index = 0;
        firstSet = false;
        secondSet = false;
        thirdSet = false;
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
  if (DEBUG) {
    Serial.print("1 - ");
    Serial.println(fullCode1);
    Serial.print("2 - ");
    Serial.println(fullCode2);
    Serial.print("3 - ");
    Serial.println(fullCode3);
    Serial.print("4 - ");
    Serial.println(fullCode4);
    Serial.println(" - ");
    delay(500);
  }

  if (fullCode2 == fullCode3 && fullCode3 == fullCode4) {
    if (DEBUG) {
      Serial.println("SUCCESS");
      Serial.println(fullCode2);
    }
    else {
      Keyboard.println(fullCode2);
    }
    delay(3000);
  }

  Serial1.begin(9600);

  fullCode1 = "";
  fullCode2 = "";
  fullCode3 = "";
  fullCode4 = "";
  readTest = "";
  firstDone = false;
  secondDone = false;
  thirdDone = false;
  firstSet = false;
  secondSet = false;
  thirdSet = false;
  index = 0;
}

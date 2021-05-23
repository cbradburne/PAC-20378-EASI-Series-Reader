/*

  PAC Easi Series 20378 reader for EasiKey 1000
  Arduino Leonardo 32u4 3.3v board (Pro Micro) for keyboard HUD mode

  Use:
  RX for Sig
  Gnd to Gnd
  12k resistor between VCC (3.3v) and RX pin
  
*/

#include <Keyboard.h>

bool DEBUG = false;

int index = 0;
int counter = 0;
bool firstSet = false;
bool secondSet = false;
bool thirdSet = false;
bool firstDone = false;
bool secondDone = false;
byte variable1[17];
byte variable2[17];
byte variable3[17];
String readTest = "";
String fullCode1 = "";
String fullCode2 = "";
String fullCode3 = "";

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

  if (firstDone && secondDone) {
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
  if (DEBUG) {
    Serial.print("1 - ");
    Serial.println(fullCode1);
    Serial.print("2 - ");
    Serial.println(fullCode2);
    Serial.print("3 - ");
    Serial.println(fullCode3);
    Serial.println(" - ");
    delay(500);
  }

  if (fullCode1 == fullCode2 && fullCode2 == fullCode3) {
    if (DEBUG) {
      Serial.println("SUCCESS");
      Serial.println(fullCode1);
      Serial.println(" - ");
    }
    else {
      Keyboard.println(fullCode1);
    }
    delay(3000);
  }

  Serial1.begin(9600);

  fullCode1 = "";
  fullCode2 = "";
  fullCode3 = "";
  firstDone = false;
  secondDone = false;
}
/*
  SPI Bus
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/sturdy-octo-goggles/blob/master/LICENSE
*/

#include <SPI.h>

const int CS1 = 10; //cs pot 1
const int CS2 = 9; //cs pot 2
const int POT1 = A1; //wiper pot 1
const int POT2 = A2; //wiper pot 2
const byte address = 0x00;

float voltage1; //volts for pot 1
float voltage2; //volts for pot 2

void setup() {
  pinMode (CS1, OUTPUT);
  pinMode (CS2, OUTPUT);
  pinMode (POT1, INPUT);
  pinMode (POT2, INPUT);
  SPI.begin();
  Serial.begin (115200);
}

void loop() {
  for (int i = 0; i <= 128; i++) //7 bits addressing for the pot wiper
  {
    //increase resistance of pot 1
    digitalWrite(CS1, LOW);
    SPI.transfer(address);
    SPI.transfer(i);
    digitalWrite(CS1, HIGH);
    voltage1 = analogRead (POT1) / 1023.0 * 5.0;
    //decrease resistance of pot 2
    digitalWrite(CS2, LOW);
    SPI.transfer(address);
    SPI.transfer(128 - i);
    digitalWrite(CS2, HIGH);
    voltage2 = analogRead (POT2) / 1023.0 * 5.0;
    Serial.print ("Pot 1: ");
    Serial.print (voltage1);
    Serial.print ("V     ");
    Serial.print ("Pot 2: ");
    Serial.print (voltage2);
    Serial.println ("V ");
    delay(200);
  }
  delay(500);
  for (int i = 0; i <= 128; i++)
  {
    //decrease resistance of pot 1
    digitalWrite(CS1, LOW);
    SPI.transfer(address);
    SPI.transfer(128 - i);
    digitalWrite(CS1, HIGH);
    voltage1 = analogRead (POT1) / 1023.0 * 5.0;
    //increase resistance of pot 2
    digitalWrite(CS2, LOW);
    SPI.transfer(address);
    SPI.transfer(i);
    digitalWrite(CS2, HIGH);
    voltage2 = analogRead (POT2) / 1023.0 * 5.0;
    Serial.print ("Pot 1: ");
    Serial.print (voltage1);
    Serial.print ("V     ");
    Serial.print ("Pot 2: ");
    Serial.print (voltage2);
    Serial.println ("V ");
    delay(200);
  }
}

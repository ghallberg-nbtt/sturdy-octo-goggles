/*
  The AREF Pin
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/sturdy-octo-goggles/blob/master/LICENSE
*/

const int pot = A0;

void setup() {
  Serial.begin (9600);
}

void loop() {
  int val = analogRead(pot);
  Serial.println (val);
  delay (500);
}

/*
  Serial Monitor
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/sturdy-octo-goggles/blob/master/LICENSE
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); //Ensure LED is off
  Serial.begin (38400); //initiate serial monitor at 38400bps
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    byte incomingByte = Serial.read();
    //1 = on and 0 = off
    if (incomingByte == 49) {
      digitalWrite(LED_BUILTIN, HIGH); //Turn on LED
      Serial.println ("LED on");
    } else if (incomingByte == 48) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println ("LED off");
    } else {
      Serial.println ("invalid input");
    }
  }
}

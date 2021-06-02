/*
  Hardware Interrupts
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/sturdy-octo-goggles/blob/master/LICENSE
*/

//Define colors
const int RED = 11;
const int GREEN = 10;
const int BLUE = 9;

//Define button switch pin
const int SWITCH = 2;

//Volatile variables can be changed within the interrupt routine
volatile int color = RED; //initial color red

void setup() {
  pinMode (RED, OUTPUT);
  pinMode (GREEN, OUTPUT);
  pinMode (BLUE, OUTPUT);

  //Turn LED off
  digitalWrite (RED, LOW);
  digitalWrite (GREEN, LOW);
  digitalWrite (BLUE, LOW);

  //Attach interrupt
  //Switch press will be rising edge due to Schmitt Trigger inversion
  attachInterrupt(digitalPinToInterrupt(2), changeColor, RISING);
}

void loop() {
  //Brighten LED
  for (int i = 0; i <= 255; i++) {
    analogWrite (color, i);
    delay (10);
  }
  //Dim the LED
  for (int i = 255; i >= 0; i--) {
    analogWrite (color, i);
    delay (10);
  }
  delay (500);
}

void changeColor () {
  //Turn off current LED
  digitalWrite (color, LOW);
  //Select a new color
  if (color == RED) {
    color = GREEN;
  } else if (color == GREEN) {
    color = BLUE;
  } else {
    color = RED;
  }
}

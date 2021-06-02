/*
  Timed Interrupts
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/sturdy-octo-goggles/blob/master/LICENSE
*/

#include <TimerOne.h>

/*
  This Sketch was written with SimpleDHT version 1.0.11
  The code may need to be modified if other verions are used
*/
#include <SimpleDHT.h>

// assign I/O pins
const int SWITCH = 2;
const int LED = 12;

// variables that will change value

volatile int units = 1;  // Celsius or Fahrenheit selected

// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 8
int pinDHT11 = 8;
SimpleDHT11 dht11(pinDHT11);

void setup() {
  // set I/O pins
  pinMode (LED, OUTPUT);
  //Attach interrupt
  //Switch press will be rising edge due to Schmitt Trigger inversion
  attachInterrupt(digitalPinToInterrupt(2), changeUnit, RISING);
  //Initialize Serial monoitor for display
  Serial.begin (9600);
  //Set up timed interrupt
  Timer1.initialize (1000000); //set to 1 second in microseconds
  Timer1.attachInterrupt(flashLED); //runs flasLED on timed interrupt
}

void loop() {
  // read temperature and humidity
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("DHT11 read fail");
    Serial.println ("err="); Serial.print(err); delay(1000);
    return;
  }

  // display the results
  int tempC = temperature;
  if (units == 1) {
    Serial.print ("Temperature: ");
    Serial.print((int)temperature);
    Serial.print("C ");
    Serial.print ("Humidity: ");
    Serial.print((int)humidity);
    Serial.println("%");
    Serial.println("");
  } else {
    // convert to Fahrenheit
    temperature = ((temperature / 5) * 9) + 32;
    Serial.print ("Temperature: ");
    Serial.print((int)temperature);
    Serial.print("F ");
    Serial.print ("Humidity: ");
    Serial.print((int)humidity);
    Serial.println("%");
    Serial.println("");
  }
  delay (1500);
}


void changeUnit () {

  //Toggle C and F
  if (units == 1) {
    units = 0;
  } else {
    units = 1;
  }
}

void flashLED () {
  digitalWrite(LED, !digitalRead(LED)); //Toggle LED
}

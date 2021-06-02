/*
  I2C Clock
  Copyright 2021 Gary Hallberg
  Licensed under MIT https://github.com/ghallberg-nbtt/sturdy-octo-goggles/blob/master/LICENSE
*/

#include <Wire.h>
#include <RTClib.h>
#include <Adafruit_SSD1306.h>

char daysOfTheWeek[7][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
const int SETCLOCKPIN = 2;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 64;
const int OLED_RESET = -1; //uses Arduino reset button

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  delay(3000); // wait for console opening
  // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;); // Don't proceed, loop forever
  }

  pinMode (SETCLOCKPIN, INPUT_PULLUP);
  if (! rtc.begin()) {
    Serial.println("RTC not found");
    while (1);
  }
  if (digitalRead(SETCLOCKPIN) == LOW) {
    Serial.println("setting");
    if (rtc.lostPower()) {
      //Set time to that when program was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
      // Following line sets the RTC with an explicit date & time
      // for example to set January 27 2017 at 12:56 you would call:
      // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
    }
  }

}

void loop() {

  display.clearDisplay(); //clear display
  DateTime now = rtc.now(); //get date and time from DS3231
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(65, 50); //moves curser
  char buf_date[6];
  //formats date with leading zeros where needed
  sprintf(buf_date, "%02d/%02d", now.day(), now.month());
  display.print(buf_date);
  display.setCursor(0, 50);
  //displays day of the week
  display.print(daysOfTheWeek[now.dayOfTheWeek()]);
  display.setCursor(0, 0);
  //format the time
  char buf_time[6];
  display.setTextSize(3);
  sprintf(buf_time, "%02d:%02d", now.hour(), now.minute());
  display.print(buf_time);
  display.setCursor(88, 7);
  display.setTextSize(2);
  display.print (":");
  char buf_seconds[3];
  sprintf(buf_seconds, "%02d", now.second());
  display.print(buf_seconds);
  display.display();
  delay(1000);
}

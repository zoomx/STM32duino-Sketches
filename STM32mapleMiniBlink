/*
  STM32mapleMiniBlink  (was Blink before!)
  Turns on an LED on for 100 millisecond, then off for one 300 millisecond, repeatedly.

  Most Arduinos have an on-board LED you can control. On the Uno and
  Leonardo, it is attached to digital pin 13. If you're unsure what
  pin the on-board LED is connected to on your Arduino model, check
  the documentation at http://arduino.cc

  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald

  modified for stm32f3discovery
  2015/02 by Frank-Michael Krause

  modified  for STM32F103C8
  20/04/2015 Zoomx

  modified  for Maple Mini
  11/06/2015 Zoomx

  Use PC33 instead of PIN13 for Maple Mini boards
  Use PC13 instead of PIN13 for generic STM32 boards.
  Print on every serial to identify them.
 */

#define LED 33

void setup() {
  // initialize pins LED, as an output.
  pinMode(LED, OUTPUT);
  Serial.begin(9600);  //This is the serial over USB
  Serial1.begin(9600);  //This is the hardware serial
  Serial2.begin(9600); //This is the hardware serial
  //Serial3.begin(9600);
  Serial.println("Hello world this is Serial");
  Serial1.println("Hello world this is Serial1");
  Serial2.println("Hello world this is Serial2");
  //Serial3.println("Hello world this is Serial3");
}


void loop() {
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(300);
  Serial.println("It Works on serial");
  Serial1.println("It Works on serial1");
  Serial2.println("It Works on serial2");
  //Serial3.println("It Works on serial3");
}

#include <Arduino.h>
#include <Adafruit_CCS811.h>
#include <Wire.h>
#include <SPI.h>

void setup() {
  // initialize digital pin GIOP18 as an output.
  pinMode(2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(2, HIGH); // turn the LED on
  delay(500);             // wait for 500 milliseconds
  digitalWrite(2, LOW);  // turn the LED off
  delay(500);             // wait for 500 milliseconds
}
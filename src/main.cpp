#include <Arduino.h>
#include <Adafruit_CCS811.h>
#include <Wire.h>
#include <SPI.h>
Adafruit_CCS811 miccs;

void setup() {
  Serial.begin(9600);

  Serial.println("miccs811 test");

  if(!miccs.begin()){
    Serial.println("Failed to start sensor! Please check your wiring.");
    while(1);
  }

  // Wait for the sensor to be ready
  while(!miccs.available());
}

void loop() {
  if(miccs.available()){
    if(!miccs.readData()){
      Serial.print("CO2: ");
      Serial.print(miccs.geteCO2());
      Serial.print("ppm, TVOC: ");
      Serial.println(miccs.getTVOC());
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(500);
}
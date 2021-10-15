//##Libraries##
#include <DHT.h>
#include <Ezo_i2c.h> 
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
//##Header-Files##
#include "globalVariables.h"
//##Object intialization##
//#TempHum#
#define DHTTYPE DHT22 
DHT dht(TempHum, DHTTYPE);
//#Watertemp
OneWire oneWire(WaterTemp);
DallasTemperature waterTemp(&oneWire);
//#PH&EC#
Ezo_board EC = Ezo_board(99, "PH");      
Ezo_board RTD = Ezo_board(101, "EC");

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  unsigned long currentTime = millis();
  if ( currentTime - previousTime >= sampInterval ) {
    previousTime = currentTime;
    timer++;
    if (timer>= 1000){
      timer = 0;
      sampleFlagBottom = true;
    }
    //#State Machines
    FSM_Sensordata();
  }
}

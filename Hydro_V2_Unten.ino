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
DHT dhtSensor(TempHum, DHTTYPE);
//#Watertemp
OneWire oneWire(WaterTemp);
DallasTemperature waterTempSensor(&oneWire);
//#PH&EC#
Ezo_board phSensor(99, "PH");      
Ezo_board ecSensor(101, "EC");

void setup() {
  Serial.begin(9600);
  dhtSensor.begin();
  Wire.begin();
}

void loop() {
  unsigned long currentTime = millis();
  if ( currentTime - previousTime >= systemPeriod ) {
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

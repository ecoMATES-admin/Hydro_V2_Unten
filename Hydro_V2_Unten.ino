//##Libraries##
#include <DHT.h>
#include <Ezo_i2c.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <HCSR04.h>
#include <mcp2515.h>
//##Header-Files##
#include "globalVariables.h"
#include "MOSFET.h"
#include "CAN.h"
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
//#Ultrasonnic
HCSR04 hc(Trig, Echo); //HCSR04 (trig pin , echo pin)
//#Mosfet
MOSFET fan(CirculationFan);
//#Can
CanBuffer canBuffer;
CanFloatBuffer canFloatBuffer;
//Objects Can Comm
volatile CanFrameStream cfStream;
MCP2515 mcp2515(A3); //SS pin A3

void setup() {
  //#Objects
  Serial.begin(9600);
  dhtSensor.begin();
  Wire.begin();
  SPI.usingInterrupt(0);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_16MHZ);
  mcp2515.setNormalMode();
  //#Pins
  pinMode(Pump, OUTPUT);
  attachInterrupt(0, irqHandler, FALLING);
  pumpFlag = true; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
}

void loop() {
  unsigned long currentTime = millis();
  if ( currentTime - previousTime >= systemPeriod ) {
    previousTime = currentTime;

    //#State Machines
    //FSM_Sensordata();
    FSM_Pump();
    FSM_CirculationFan();
    FSM_CanRead();
    masterDummy();

  }
}

void masterDummy() {
  if (Serial.available() > 0) {
    int message = Serial.parseInt();
    Serial.println(message);
    if (message == 1) {
      message = 0;
      testFlag = true;
    }
  }
  if (pumpFlag)
    pumpFlag = false;

  timer++;
  if (timer == 1000) {
    circulationFanOnFlag = false;
  }else if (timer==2000){
        timer = 0;
    circulationFanOnFlag = true;
  }
};

//##Libraries##
#include <Ezo_i2c.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <HCSR04.h>
#include <mcp2515.h>
#include <Adafruit_SHT31.h>
//##Header-Files##
#include "globalVariables.h"
#include "MOSFET.h"
#include "CAN.h"
//##Object intialization##
//#TempHum#
Adafruit_SHT31 shtBottom = Adafruit_SHT31();
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
volatile CanBuffer canBuffer;
volatile CanFloatBuffer canFloatBuffer;
//Objects Can Comm
volatile CanFrameStream cfStream;
MCP2515 mcp2515(A3); //SS pin A3

void setup() {
  //#Objects
  Serial.begin(9600);
  Wire.begin();
  //TempHum
  if (! shtBottom.begin(0x44) && DEBUG)   
    Serial.println("Couldn't find shtBottom");
  shtBottom.heater(false);
  if (shtBottom.isHeaterEnabled()){
    Serial.println("shtBottom heater is ON");
  }
  SPI.usingInterrupt(InterruptPin);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_16MHZ);
  mcp2515.setNormalMode();
  //#Pins
  pinMode(Pump, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(InterruptPin, irqHandler, FALLING);
}

void loop() {
  unsigned long currentTime = millis();
  if ( currentTime - previousTime >= systemPeriod ) {
    previousTime = currentTime;
    //#CAN
    canRead();
    
    //#State Machines
    FSM_CanRead();
    FSM_Sensordata();
    FSM_Pump();
    FSM_Leds();
    FSM_CirculationFan();
    //masterDummy();

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
};

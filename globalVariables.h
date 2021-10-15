#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

//## Pinning##
//#Sensors
#define TempHum 3
#define WaterTemp 4
#define Trig A2
#define Echo A1
//#Actuators
#define Pump 6
#define LED 7
#define DIMM 0
#define Circulation 10

//##Variables##
//#SystemClock
unsigned long previousTime = 0; 
unsigned long sampInterval = 10; // milliseconds
//#SystemTiming
int timer = 0;
bool sampleFlagBottom = false;

//#FSM_Sensordata
uint8_t sensorState =0; 
float tempHumVal[2] = {0};
enum SensorStates{
  Idle, ReadTempBottom,ReadTempWater, RequestPH, RequestEC, ReadPH, ReadEC, 
};





#endif

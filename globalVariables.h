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
//#Debug#
#define DEBUG 1
bool testFlag = false;
//#SystemClock
unsigned long previousTime = 0; 
unsigned long systemPeriod = 10; // milliseconds
//#SystemTiming
int timer = 0;
bool sampleFlagBottom = false;
bool pumpFlag = false;

//#FSM_Sensordata
uint8_t sensorCounter = 0; 
float tempHumVal[2] = {0};
float waterTempVal = 0;
float phVal = 0;
float ecVal = 0;
enum class sensorStates:uint8_t{
  Idle, ReadTempBottom,ReadTempWater, RequestEZO, AwaitEZO, ReadEZO, 
};
sensorStates sensorState =sensorStates::Idle;

//#FSM_Pump
uint16_t pumpCounter = 0;
float distance = 0;
float n = 600;
float meanDistance = 0;
enum class pumpStates:uint8_t{
  Idle, PumpOn, PumpOff, ReadWaterLevel
};
pumpStates  pumpState = pumpStates::Idle;


#endif

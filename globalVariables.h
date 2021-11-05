#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

//## Pinning##
#define InterruptPin 0 //Arduino pin 2
//#Sensors
#define TempHum 3
#define WaterTemp 4
#define Trig A2
#define Echo A1
//#Actuators
#define Pump 6
#define LED 7
#define DIMM 0
#define CirculationFan 10

#define MSB 1
#define LSB 0

//##Variables##
//#Debug#
#define DEBUG 1
bool testFlag = false;
//#SystemClock#
unsigned long previousTime = 0; 
unsigned long systemPeriod = 10; // milliseconds
//#SystemTiming#
int timer = 0;
bool sampleFlagBottom = false;
bool pumpFlag = false;
bool ledFlag = false;
bool circulationFanOnFlag = true;

//#FSM_Sensordata#
uint8_t sensorCounter = 0; 
float tempHumVal[2] = {0};
float waterTempVal = 0;
float phVal = 0;
float ecVal = 0;
enum class sensorStates:uint8_t{
  Idle, ReadTempBottom,ReadTempWater, RequestEZO, AwaitEZO, ReadEZO, 
};
sensorStates sensorState =sensorStates::Idle;

//#FSM_Pump#
uint16_t pumpCounter = 0;
float distance = 0;
float n = 600;
float meanDistance = 0;
typedef struct {uint8_t x; float y;} point;
const uint8_t waterLevelArraySize = 19;
point point2, point1;
float m, waterLevelVal = 0;
point waterLevelArray [waterLevelArraySize] = 
{
{0, 32.89},
{1, 31.86},
{2, 29.99},
{3, 28.94},
{4, 27.86},
{5, 26.11},
{6, 25.06},
{7, 23.29},
{8, 22.34},
{9, 20.81},
{10, 20.48},
{11, 18.87},
{12, 17.25},
{13, 16.34},
{14, 14.99},
{15, 14.34},
{16, 13.64},
{17, 12.57},
{18, 11.18}
};
enum class pumpStates:uint8_t{
  Idle, PumpOn, PumpOff, ReadWaterDistance, CalculateWaterLevel
};
pumpStates  pumpState = pumpStates::Idle;

//#FSM_CirculationFan#
enum class circulationFanStates:uint8_t{
  FanOn, FanOff
};
circulationFanStates circulationFanState = circulationFanStates::FanOn;

//#FSM_CanRead#
volatile bool interrupt = false;
volatile bool mcp2515_overflow = false;
volatile bool arduino_overflow = false;
union my_can_msg {
  unsigned long value;
  unsigned char bytes[4];
};

//FSM_Leds#
enum class ledsStates:uint8_t{
  LedsOn, LedsOff
};
ledsStates ledsState = ledsStates::LedsOff;

#endif

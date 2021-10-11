#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

//## Pinning##
//#Sensoren
#define T&H 3
#define WaterTemp 4
#define Trig A2
#define Echo A1
//#Aktoren
#define Pumpe 6
#define LED 7
#define DIMM 0
#define Umluft 10

//##Variablen##
//#SystemTiming

//#FSM_Sensordaten
uint8_t sensorState =0; 
enum SensorStates{
  Idle, ReadTempUnten, ReadPH, ReadEC, ReadTempWasser
};





#endif

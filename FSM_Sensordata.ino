
void FSM_Sensordata() {
  switch (sensorState) {
    case Idle:
      if(sampleFlagBottom){
        sampleFlagBottom = false;
        sensorState++;
      }
      break;
    case ReadTempBottom:
      if (!dht.readTempAndHumidity(tempHumVal)) {
        Serial.print("H1: ");
        Serial.print(tempHumVal[0]);
        Serial.print(" %\t");
        Serial.print("T1: ");
        Serial.print(tempHumVal[1]);
        Serial.println(" *C");
        sensorState++;
      }else {
        Serial.println("Failed to get temprature and humidity value.");
      }
      break;
      case ReadTempWater:
        waterTemp.requestTemperatures();
        Serial.print("Watertemperature is: ");
        Serial.println(waterTemp.getTempCByIndex(0));
        sensorState = Idle;
      break;
      case RequestPH:
      break;
      case RequestEC:
      break;
    case ReadPH:
      break;
    case ReadEC:
      break;
    
    default:
      Serial.println("Bug FSM_Sensordata");
  }
};

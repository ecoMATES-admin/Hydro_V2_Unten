

void FSM_Pump() {
  switch (pumpState) {
    case pumpStates::Idle:
      if (pumpFlag) {
        pumpState = pumpStates::PumpOn;
      }
      break;
    case pumpStates::PumpOn: //Übergangn gemessen: pumpCounter == 8072
      digitalWrite(Pump, HIGH);
      pumpCounter++;
      if (pumpCounter == 8072) {
        pumpCounter = 0;
        pumpState = pumpStates::PumpOff;
      }
      break;
    case pumpStates::PumpOff:  //Übergangn gemessen: pumpCounter == 21067
      digitalWrite(Pump, LOW);
      pumpCounter++;
      if (pumpCounter == 21067) {
        pumpCounter = 0;
        pumpState = pumpStates::ReadWaterLevel;
      }
      break;
    case pumpStates::ReadWaterLevel:
      distance = hc.dist();
      if (DEBUG)
        Serial.println( distance );
      meanDistance += distance;
      pumpCounter++;
      if (pumpCounter == int(n)) {
        pumpCounter=0;
        meanDistance = meanDistance / n;
        if(DEBUG){
        Serial.println("Mittelwert:");
        Serial.println(meanDistance);
        }
        pumpState = pumpStates::Idle;
      }
      break;
    default:
      Serial.println("Error: FSM_Pump()");
  }
};



void FSM_Pump(){
  switch(pumpState){
    case pumpStates::Idle:
    if(pumpFlag){
      pumpState = pumpStates::PumpOn;
    }
    break;
    case pumpStates::PumpOn:
    digitalWrite(Pump, HIGH);
    pumpCounter++;
    if(pumpFlag){
      Serial.print("pumpOn Time: ");
      Serial.println(pumpCounter);
      pumpCounter = 0;
      pumpFlag=false;
      pumpState=pumpStates::PumpOff;
    }
    break;
    case pumpStates::PumpOff:
    digitalWrite(Pump, LOW);
    pumpCounter++;
    if(pumpFlag){
      Serial.print("pumpOff Value: ");
      Serial.println(pumpCounter);
      pumpCounter = 0;
      pumpFlag=false;
      pumpState=pumpStates::ReadWaterLevel;
    }
    break;
    case pumpStates::ReadWaterLevel:
    distance = hc.dist();
    Serial.println( distance );
    meanDistance += distance;
    pumpCounter++;
    if(pumpCounter == 600){
      meanDistance = meanDistance/n;
  Serial.println("Mittelwert:");
  Serial.println(meanDistance);
    }
    break;
    default:
    Serial.println("Error: FSM_Pump()");
  }
};

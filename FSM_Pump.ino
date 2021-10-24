

void FSM_Pump() {
  uint8_t exponent;
  switch (pumpState) {
    case pumpStates::Idle:
      if (pumpFlag) {
        pumpFlag = false;
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
        pumpState = pumpStates::ReadWaterDistance;
      }
      break;
    case pumpStates::ReadWaterDistance:
      distance = hc.dist();
      if (DEBUG)
        Serial.println( distance );
      meanDistance += distance;
      pumpCounter++;
      if (pumpCounter == int(n)) {
        pumpCounter = 0;
        meanDistance = meanDistance / n;
        if (DEBUG) {
          Serial.print("Mittelwert Distanz:");
          Serial.println(meanDistance);
        }
        pumpState = pumpStates::CalculateWaterLevel;
      }
      break;
    case pumpStates::CalculateWaterLevel:
      if (meanDistance <= waterLevelArray[waterLevelArraySize - 1].y) {
        waterLevelVal = 18.0;
      } else if (meanDistance >= waterLevelArray[0].y) {
        waterLevelVal = 0.0;
      } else {
        for (uint8_t i = waterLevelArraySize - 1; i >= 0; i--) {
          if (meanDistance <= waterLevelArray[i].y) {
            point2 = waterLevelArray[i];
            point1 = waterLevelArray[i + 1];
            break;
          }
        }
        m = (point2.y - point1.y) / (float(point2.x - point1.x));
        waterLevelVal = 1 / m * (meanDistance - point1.y) + float(point1.x);
      }
      exponent = getExponent(waterLevelVal);
      canWrite(8,exponent,floatToCan(waterLevelVal,exponent));
      if (DEBUG) {
        Serial.print("point1.x:");
        Serial.println(point1.x);
        Serial.print("point1.y:");
        Serial.println(point1.y);
        Serial.print("point2.x:");
        Serial.println(point2.x);
        Serial.print("point2.y:");
        Serial.println(point2.y);
        Serial.print("m:");
        Serial.println(m);
        Serial.print("Wasserstand:");
        Serial.println(waterLevelVal);
      }
      pumpState = pumpStates::Idle;
      break;
    default:
      Serial.println("Error: FSM_Pump()");
  }
};

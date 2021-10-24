
void FSM_Sensordata() {
  uint8_t exponent1, exponent2;
  switch (sensorState) {
    case sensorStates::Idle:
      if (sampleFlagBottom) {
        sampleFlagBottom = false;
        sensorState=sensorStates::ReadTempBottom;
      }
      break;
    case sensorStates::ReadTempBottom:
      if (!dhtSensor.readTempAndHumidity(tempHumVal)) {
        exponent1 = getExponent(tempHumVal[1]);
        exponent2 = getExponent(tempHumVal[0]);
        canWrite(3,exponent1, floatToCan(tempHumVal[1],exponent1));
        canWrite(4,exponent2, floatToCan(tempHumVal[0],exponent2));
        if (DEBUG) {
          Serial.print("H1: ");
          Serial.print(tempHumVal[0]);
          Serial.print(" %\t");
          Serial.print("T1: ");
          Serial.print(tempHumVal[1]);
          Serial.println(" *C");
        }
        sensorState = sensorStates::ReadTempWater;
      } else {
        Serial.println("Error: Failed to get temprature and humidity value.");
      }
      break;
    case sensorStates::ReadTempWater:
      waterTempSensor.requestTemperatures();
      waterTempVal = waterTempSensor.getTempCByIndex(0);
      exponent1 = getExponent(waterTempVal);
      canWrite(5,exponent1,floatToCan(waterTempVal,exponent1));
      if (DEBUG) {
        if (waterTempVal == -7040) { //information taken from library
          Serial.println("Error: Failed to get new watertemp value.");
        } else {
          Serial.print("WaterTemp: ");
          Serial.println(waterTempVal);
        }
      }
      sensorState = sensorStates::RequestEZO;
      break;
    case sensorStates::RequestEZO:
      phSensor.send_read_with_temp_comp(waterTempVal);
      ecSensor.send_read_with_temp_comp(waterTempVal);
      sensorState = sensorStates::AwaitEZO;
      break;
    case sensorStates::AwaitEZO:
      sensorCounter++;
      if (sensorCounter * systemPeriod >= 900) {
        sensorCounter = 0;
        sensorState=sensorStates::ReadEZO;
      }
      break;
    case sensorStates::ReadEZO:
      phSensor.receive_read_cmd();
      ecSensor.receive_read_cmd();
      if (phSensor.get_error() == Ezo_board::SUCCESS) {
        phVal = phSensor.get_last_received_reading();
      } else {
        //watchdog
        Serial.println("Error: No new valid PH reading");
      }
      if (ecSensor.get_error() == Ezo_board::SUCCESS) {
        ecVal = ecSensor.get_last_received_reading();
      } else {
        //watchdog
        Serial.println("Error: No new valid EC reading");
      }
        exponent1 = getExponent(phVal);
        exponent2 = getExponent(ecVal);
        canWrite(7,exponent1, floatToCan(phVal,exponent1));
        canWrite(6,exponent2, floatToCan(ecVal,exponent2));
      if (DEBUG) {
        Serial.print("PH: ");
        Serial.print(phVal);
        Serial.print("\t");
        Serial.print("EC: ");
        Serial.println(ecVal);
      }
      sensorState = sensorStates::Idle;
      break;
    default:
      Serial.println("Error: FSM_Sensordata default state");
  }
};

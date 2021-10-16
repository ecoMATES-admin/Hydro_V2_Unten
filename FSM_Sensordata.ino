
void FSM_Sensordata() {
  switch (sensorState) {
    case Idle:
      if (sampleFlagBottom) {
        sampleFlagBottom = false;
        sensorState++;
      }
      break;
    case ReadTempBottom:
      if (!dhtSensor.readTempAndHumidity(tempHumVal)) {
        if (DEBUG) {
          Serial.print("H1: ");
          Serial.print(tempHumVal[0]);
          Serial.print(" %\t");
          Serial.print("T1: ");
          Serial.print(tempHumVal[1]);
          Serial.println(" *C");
        }
        sensorState++;
      } else {
        Serial.println("Error: Failed to get temprature and humidity value.");
      }
      break;
    case ReadTempWater:
      waterTempSensor.requestTemperatures();
      waterTempVal = waterTempSensor.getTempCByIndex(0);
      if (DEBUG) {
        if (waterTempVal == -7040) {
          Serial.println("Error: Failed to get new watertemp value.");
        } else {
          Serial.print("WaterTemp: ");
          Serial.println(waterTempVal);
        }
      }
      sensorState++;
      break;
    case RequestEZO:
      phSensor.send_read_with_temp_comp(waterTempVal);
      ecSensor.send_read_with_temp_comp(waterTempVal);
      sensorState++;
      break;
    case AwaitEZO:
      counterEZO++;
      if (counterEZO * systemPeriod >= 900) {
        counterEZO = 0;
        sensorState++;
      }
      break;
    case ReadEZO:
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
      if (DEBUG) {
        Serial.print("PH: ");
        Serial.print(phVal);
        Serial.print("\t");
        Serial.print("EC: ");
        Serial.println(ecVal);
      }
      sensorState = 0;
      break;
    default:
      Serial.println("Error: FSM_Sensordata default state");
  }
};

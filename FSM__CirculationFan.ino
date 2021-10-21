
void FSM_CirculationFan() {
  switch (circulationFanState) {
    case circulationFanStates::FanOn:
      fan.on();
      if (!circulationFanOnFlag) {
        circulationFanState = circulationFanStates::FanOff;
      }
      break;
    case circulationFanStates::FanOff:
      fan.off();
      if (circulationFanOnFlag) {
        circulationFanState = circulationFanStates::FanOn;
      }
      break;
      default:
      Serial.println("Error: FSM_CirculationFan()");
  }
}

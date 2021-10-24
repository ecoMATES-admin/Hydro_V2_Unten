void FSM_Leds(){
  switch(ledsState){
    case ledsStates::LedsOn:
    digitalWrite(LED, HIGH);
    if(!ledFlag){
      ledsState = ledsStates::LedsOff;
    }
    break;
    case ledsStates::LedsOff:
    digitalWrite(LED, LOW);
    if(ledFlag){
      ledsState = ledsStates::LedsOn;
    }
    break;
  }
}

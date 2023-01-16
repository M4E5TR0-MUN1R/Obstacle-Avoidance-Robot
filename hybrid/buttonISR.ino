long last_micros = 0;

void buttonISR() {
  //Serial.println("==INTERRUPT!==");
  if ((micros() - last_micros) >= 200000 )
  {
    //state = !state;
    if (state < 3)
    {
      state++;
    }
    else
    {
      state = 0;
    } 
    last_micros = micros();
    int give = int(state);
    modeSwitch(give);
    stateUpdate();
  }
  
  /*DEBUG
  if( state == 0)
  {
    Serial.println("==MODE IS ZERO==");
  }
  else if (state == 1)
  {
    Serial.println("==MODE IS ONE==");    
  }
  else
  {
    Serial.println("==MODE IS TWO==");
  }*/
}

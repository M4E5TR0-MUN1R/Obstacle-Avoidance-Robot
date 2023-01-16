int ledState = LOW;
boolean buttonState = LOW; 
int pressed=0;

void buttonCheck() {
  if(debounceButton(buttonState) == HIGH && buttonState == LOW)
  {
    pressed++;
    buttonState = HIGH;
  }
  else if(debounceButton(buttonState) == LOW && buttonState == HIGH)
  {
       buttonState = LOW;
  }
   if(pressed == 2)
  {
    //digitalWrite(ledPin,HIGH);
    //Serial.println("==MODE SWITCHED==");
    if (mode == 1)
    {
      mode = 0;
      //Serial.println("==MODE IS LOW==");
    }
    else
    {
      mode = 1;
      //Serial.println("==MODE IS HIGH==");
    }
    pressed = 0;
  }
}

boolean debounceButton(boolean state)
{
  boolean stateNow = digitalRead(buttonPin);
  if(state!=stateNow)
  {
    delay(10);
    stateNow = digitalRead(buttonPin);
  }
  return stateNow;
  
}

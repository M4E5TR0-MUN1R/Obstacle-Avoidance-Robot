void irMode()
{
    //Serial.println("==IR MODE==");
    //Enable The IR Sensors
    digitalWrite(EnIR,HIGH); 
    /*
    analogWrite(EnA,110);
    analogWrite(EnB,110);
    */
   //use state for interrupts or mode for button press
   while( state == 3)
   {
    parsing();
    stateUpdate();
    //left sensor input 
    int l1=digitalRead(leftIR); 
    //Right Sensor Input 
    int r1=digitalRead(rightIR);
     
    if((l1==LOW)&&(r1==LOW)) 
    { 
       //Stay still
      //Serial.println("==OBJECT ON BOTH SIDES==");
      Stop();
      delay(300);
      moveBackward();
      delay(600);
      right();
      delay(250);
    } else if((l1==LOW)&&(r1==HIGH)) {
        //turns right
        //Serial.println("==OBJECT ON LEFT SIDE=="); 
        right();
    } else if((l1==HIGH)&&(r1==LOW)) {
          //turns left
          //Serial.println("==OBJECT ON RIGHT SIDE=="); 
          left(); 
    } else if((l1==HIGH)&&(r1==HIGH)) {
          //Forward
        //Serial.println("==NO OBJECT DETECTED==");
         forward();
    }
   parsing();
   stateUpdate();
  }   
    
}

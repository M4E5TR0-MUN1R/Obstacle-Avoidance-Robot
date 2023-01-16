/*******************Motor Commands**********************/
void forward() {
  digitalWrite(RightMotorForward,HIGH);
  digitalWrite(RightMotorBackward,LOW); 
  digitalWrite(LeftMotorForward,HIGH); 
  digitalWrite(LeftMotorBackward,LOW);
}
void left() {
  //Serial.println("Turn Left");
  digitalWrite(RightMotorForward,LOW); 
  digitalWrite(RightMotorBackward,HIGH); 
  digitalWrite(LeftMotorForward,HIGH); 
  digitalWrite(LeftMotorBackward,LOW); 
}
void right() {
  //Serial.println("Turn Right");
  digitalWrite(RightMotorForward,HIGH); 
  digitalWrite(RightMotorBackward,LOW); 
  digitalWrite(LeftMotorForward,LOW); 
  digitalWrite(LeftMotorBackward,HIGH); 
}
void Stop() {
  digitalWrite(RightMotorForward,LOW); 
  digitalWrite(RightMotorBackward,LOW); 
  digitalWrite(LeftMotorForward,LOW); 
  digitalWrite(LeftMotorBackward,LOW);
  leftsensor = leftSensor();
  rightsensor = rightSensor();
}

void uturn()
{
    digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  
   delay(770);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

 
}

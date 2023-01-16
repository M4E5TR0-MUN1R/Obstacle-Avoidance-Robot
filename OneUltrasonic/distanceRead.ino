int distanceRead(int pingPin, int echoPin)
{
   //Read Distance from an Ultrasonic Sensor
   long duration, cm;
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   duration = pulseIn(echoPin, HIGH);
   cm = microsecondsToCentimeters(duration);
   if (pingPin == 11){
   Serial.print("LEFT: ");
   Serial.print(cm);
   Serial.println();
   }
   else 
   {
   Serial.print("RIGHT: ");
   Serial.print(cm);
   Serial.println(); 
   }
}


long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}

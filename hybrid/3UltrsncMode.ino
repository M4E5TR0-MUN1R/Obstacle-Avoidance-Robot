NewPing sonar1(trig_pin1, echo_pin1, maximum_distance);
NewPing sonar2(trig_pin2, echo_pin2, maximum_distance);
NewPing sonar3(trig_pin3, echo_pin3, maximum_distance);

/*
NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(trig_pin1, echo_pin1, maximum_distance), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(trig_pin2, echo_pin2, maximum_distance), 
  NewPing(trig_pin3, echo_pin3, maximum_distance)
};
*/
void Ultrsnc3Mode()
{ 
  //Disable The IR Sensors
  digitalWrite(EnIR,LOW);
  //Enable Ultrasonic Sensors
  digitalWrite(EnUltrsnc,HIGH);
  
  //Set the speed of the motors
  RmotSpeed = 100;
  LmotSpeed = 100;
  analogWrite(EnA,LmotSpeed);
  analogWrite(EnB,RmotSpeed);
  while (state == 2)
  {
    parsing();
    stateUpdate();
    run3UltrasncMode();
    parsing();
    stateUpdate();
  }
}

void run3UltrasncMode() {
  centersensor = centerSensor();
  leftsensor = leftSensor();
  rightsensor = rightSensor();
  String _centersensor = String(centersensor);
  String _leftsensor = String(leftsensor);
  String _rightsensor = String(rightsensor);
  /*
  Serial.println("F:"+_centersensor);
  Serial.println("L:"+_leftsensor);
  Serial.println("R:"+_rightsensor);
  */
// Check the distance using the IF condition
  if (centersensor <= fwSensitivity) {
    Stop();
    delay(300);
    moveBackward();
    delay(400);
    left();
    delay(300);
    //Serial.println("Stop");
    /*
    if (leftsensor > rightsensor) {
      left();
      //Serial.println("Left");
      delay(turnDelayUSM);
    } else {
      right();
      //Serial.println("Right");
      delay(turnDelayUSM);
    }
    */
  }
  else if (leftsensor <= sensitivityULTRSNCMode)
  {
   right();
   delay(avoidDelay);
  }
    else if (rightsensor <= sensitivityULTRSNCMode)
  {
   left(); 
   delay(avoidDelay);
  }
  //Serial.println("Forward");
  forward();
  
}

//Get the sensor values
int leftSensor() {
   delay(100);
    int cm = sonar2.ping_cm();
    if (cm==0){
      cm=250;
      }
    int distance = cm;
    return distance;
}

//Get the sensor values
int centerSensor() {
    delay(100);
    int cm = sonar1.ping_cm();
    if (cm==0){
      cm=250;
      }
    int distance = cm;
    return distance;
}

//Get the sensor values
int rightSensor() {
    delay(100);
    int cm = sonar3.ping_cm();
    if (cm==0){
      cm=250;
      }
    int distance = cm;
    return distance;
}

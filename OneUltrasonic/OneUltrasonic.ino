const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int pingPin2 = 11; // Trigger Pin of Ultrasonic Sensor 2
const int echoPin2 = 10; // Echo Pin of Ultrasonic Sensor 2

void setup() {
   Serial.begin(9600); // Starting Serial Terminal
   pinMode(pingPin, OUTPUT);
   pinMode(pingPin2, OUTPUT);
   pinMode(echoPin, INPUT);
   pinMode(echoPin2, INPUT);

   //Right motor audrino to motor Drive 
   pinMode(0,OUTPUT); 
   pinMode(1,OUTPUT); 
   //left Motor Arduino motor Drive 
   pinMode(2,OUTPUT); 
   pinMode(3,OUTPUT); 
}

void loop() {
   //Right
   int right = distanceRead(pingPin,echoPin);
   //Left
   int left = distanceRead(pingPin2,echoPin2);
   delay(100);

    if((left <= 20 )&&(right <= 20)) 
    { 
       //Stay still
      digitalWrite(0,LOW); 
      digitalWrite(1,LOW); 
      digitalWrite(2,LOW); 
      digitalWrite(3,LOW); 
    } else if((left <= 20)&&(right >= 21)) {
        //turns right 
        digitalWrite(0,HIGH); 
        digitalWrite(1,LOW); 
        digitalWrite(2,LOW); 
        digitalWrite(3,HIGH); 
    } else if((left >= 21)&&(right <= 20)) {
          //turns left 
          digitalWrite(0,LOW); 
          digitalWrite(1,HIGH); 
          digitalWrite(2,HIGH); 
          digitalWrite(3,LOW); 
    } else if((left >= 21 )&&(right >= 21)) {
          //Stop the Boot
         digitalWrite(0,LOW);
         digitalWrite(1,HIGH); 
         digitalWrite(2,LOW); 
         digitalWrite(3,HIGH);
    }
}

#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

#include "Parser.h"
#include "AsyncStream.h"  // asynchronous read serial
AsyncStream<50> serial(&Serial, ';');   // specify handler and stop character


const int buttonPin = 0;
const byte interruptPin = 2;    
//const int ledPin =  13;  

//Operation Variables
int centersensor, leftsensor, rightsensor;
#define maximum_distance 250
#define Speed 80
int RmotSpeed = 130;
int LmotSpeed = 100;

//Operation Variables 3ultrasonic Mode
const int sensitivityULTRSNCMode = 40;
const int fwSensitivity = 40;
const int turnDelayUSM = 500;
const int avoidDelay = 250;

//Setup 3 HC-SR04
#define trig_pin1 A1
#define echo_pin1 A2
#define trig_pin2 A3
#define echo_pin2 A0
#define trig_pin3 A5
#define echo_pin3 A4
#define SONAR_NUM 3

//L298N control pins
const int RightMotorForward = 5; //in4
const int RightMotorBackward = 4;  //in3
const int LeftMotorBackward = 7; //in2
const int LeftMotorForward = 6; //in1

//IR sensor Pins
const int rightIR = 9; //Right IR Sensor
const int leftIR = 8;  //Left IR Sensor
//Enables
const int EnUltrsnc = 13; //Enable Ultra-sonic Sensors
const int EnIR = 12; //Enable IR Sensors

//Speed Setup
const int EnA = 3; //EnA
const int EnB = 11; //EnB

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

boolean goesForward = false;
int distance = 150;
NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //object of class Servo

//Mode 0 for IR and 1 for Servo
//volatile byte state = 0;
int state = 5;
int mode = 0;

void setup() {
  Serial.begin(115200);
  //Interrupt for Mode Changing
  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonISR , RISING);
  //Button for Mode changing
  pinMode(buttonPin, INPUT);
  //Mode LED indicator
  //pinMode(ledPin, OUTPUT); 
  //Enable Sensors
  pinMode(EnIR,OUTPUT);
  pinMode(EnUltrsnc,OUTPUT);
  //Right IR Sensor
  pinMode(rightIR,INPUT); 
  //Left IR Sensor
  pinMode(leftIR,INPUT);
  //Motor Setup 
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  //Speed Setup
  pinMode(EnA, OUTPUT);
  pinMode(EnB, OUTPUT);
  analogWrite(EnA,LmotSpeed);
  analogWrite(EnB,RmotSpeed);
  //Servo setup
  servo_motor.attach(10); //servo pin
  servo_motor.write(115);
  //Serial.println("==Setup Done==");
} 

long timer2 = millis();

void loop() 
{
   parsing();
   if ((timer2 - millis()) >= 500)
   {
    stateUpdate();
   }
   
   //stateUpdate();
   if(state == 0)
   {
    parsing();
    stateUpdate();
    digitalWrite(EnIR,LOW);
    digitalWrite(EnUltrsnc,LOW);
   }
   else if(state == 1)
   {
     servoMode();
   }
   else if (state == 2)
   {
    Ultrsnc3Mode();
   }
   else if (state == 3)
   {
     irMode();
   }

   /*Button Mode
   if(mode == HIGH)
   {
    servoMode();
   }
   else
   {
    irMode();
   }
   */
}
void parsing() {
  if (serial.available()) {
    Parser data(serial.buf, ',');  // give to the parser
    int ints[10];           // array for numerical data
    data.parseInts(ints);   // parse into it

    switch (ints[0]) {
      case 0:
        modeSwitch(ints[1]);
        //digitalWrite(13, ints[1]);
        break;
        
      case 1:
         analogWrite(EnA,ints[1]);
         analogWrite(EnB, ints[2]);
        //analogWrite(LED_R, ints[1]);
        //analogWrite(LED_G, ints[2]);
        //analogWrite(LED_B, ints[3]);
        break;
        
      case 2:
        servo_motor.write(ints[1]);
        break;
      case 3:
        //digitalWrite(MOS, ints[1]);
        break;
      case 4:
       // digitalWrite(RELAY, ints[1]);
        break;
      case 5:
        //data.split();
        //lcd.clear();
        //lcd.home();
        //lcd.print(data[1]);
        break;
    }
  }
}

void modeSwitch(int m)
{
  state = m;
}

long timer = millis();
void stateUpdate()
{
  if (state == 0)
  {
    Serial.print(0);
    Serial.print(',');
    Serial.print(0);
    Serial.print('\r');
    Serial.print('\n');
  }
  else if (state == 1)
  {
    Serial.print(0);
    Serial.print(',');
    Serial.print(1);
    Serial.print('\r');
    Serial.print('\n');
  }
  else if (state == 2)
  {
    Serial.print(0);
    Serial.print(',');
    Serial.print(2);
    Serial.print('\r');
    Serial.print('\n');
  }
  else if (state == 3)
  {
    Serial.print(0);
    Serial.print(',');
    Serial.print(3);
    Serial.print('\r');
    Serial.print('\n');
  }
  //parsing();
  /*
  if ((millis()-timer) >= 2000)
  {
    if (state == 0)
  {
    int packet[2];
    packet[0] = 0;
    sendPacket(0, packet, 1);
  }
  else if (state = 1)
  {
    int packet[2];
    packet[0] = 1;
    sendPacket(0, packet, 1);
  }
  else if (state = 2)
  {
    int packet[2];
    packet[0] = 2;
    sendPacket(0, packet, 1);
  }
  else if (state = 3)
  {
    int packet[2];
    packet[0] = 3;
    sendPacket(0, packet, 1);
  }
  timer = millis();
  }
  */
}

void sendPacket(int key, int* data, int amount) {
  Serial.print(key);
  Serial.print(',');
  for (int i = 0; i < amount; i++) {
    Serial.print(data[i]);
    if (i != amount - 1) Serial.print(',');
  }
  Serial.print('\r');
  Serial.print('\n');
  
}

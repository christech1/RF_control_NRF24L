#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN pins
const byte address[6] = "00001"; // Change this address to match the transmitter's address
int enA = 3;
int in1 = 4;
int in2 = 5;
 
// Motor B
 
int enB = 6;
int in3 = 7;
int in4 = 8;
int brush = 2;
//int buttonState;
 struct Data_Package {
  int joyposVert;
  int joyposHorz;
  int buttonState = 1;
  };
  Data_Package Data;
 
int MotorSpeed1 = 150;
int MotorSpeed2 = 150;
 int MotorSpeed2f = 150;
 int MotorSpeed1f = 150;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

   
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(brush, OUTPUT);
  digitalWrite(enA, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enB, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
//  Data.joyposVert = 512;
//  Data.joyposVert = 512;
digitalWrite(brush, LOW);
}

void loop() {
 
  if (radio.available()) {
    radio.read(&Data, sizeof(Data_Package));

//    Serial.println(Data.joyposVert);
//    Serial.println(Data.joyposHorz);
//    Serial.println(Data.buttonState);
    delay(500);
    
  }
if (Data.buttonState == 0){
 digitalWrite(brush, HIGH);
}
else{
  digitalWrite(brush, LOW);
}
///////////////FORWARD/////////////////
if (Data.joyposVert < 50)
  {
     analogWrite(enA, MotorSpeed1f);
     analogWrite(enB, MotorSpeed2f);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B backward
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(100);
 
    
 
  }
  /////////////REVERSE////////////
  else if (Data.joyposVert > 180)
  {
    
     analogWrite(enA, MotorSpeed1f);
     analogWrite(enB, MotorSpeed2f);
//  Serial.println("REVERSE");
     digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
 
    // Set Motor B forward
 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
 delay(100);
    //Determine Motor Speeds
 
 
  }

  // Now do the steering
  // The Horizontal position will "weigh" the motor speed
  // Values for each motor
 ////////////////RIGHT///////////////////
 else if (Data.joyposHorz < 50)
  {
   digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
 
    // Set Motor B forward
 
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
 
    //Determine Motor Speeds
 
     analogWrite(enA, MotorSpeed1);
     digitalWrite(enB, LOW);
 
  }
  ///////////////LEFT///////////////////
  else if (Data.joyposHorz > 180)
  {
    
   digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
 
    // Set Motor B forward
 
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
 
    //Determine Motor Speeds
 
     digitalWrite(enA, LOW);
     analogWrite(enB, MotorSpeed2);    
 
  }


 else
  {

 STOP();
  }

  
}




void STOP(){
    digitalWrite(enA, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(enB, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//void brush(){
//  digitalWrite(brush, HIGH);
//}

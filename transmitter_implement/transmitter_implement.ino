#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(10, 9); // CE, CSN pins
const byte address[6] = "00001"; // Change this address to match the receiver's address

int joyposVert; // Declare these variables at the global level
int joyposHorz;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(A1, INPUT); // X-axis of joystick
  pinMode(A2, INPUT); // Y-axis of joystick
  pinMode(2, INPUT_PULLUP); // Push button
}

void loop() {
  int xPosition = analogRead(A0);
  int yPosition = analogRead(A1);
  int buttonState = digitalRead(2);
  
  struct Data_Package {
    int joyposVert;
    int joyposHorz;
      int buttonState = digitalRead(2);
  } Data; // Define the struct here

  Data.joyposVert = map(xPosition, 0, 1023, 0, 255);
  Data.joyposHorz = map(yPosition, 0, 1023, 0, 255);

  Serial.println(Data.joyposVert);
  Serial.println(Data.joyposHorz);
  Serial.println(Data.buttonState);
  delay(500);
  
  radio.write(&Data, sizeof(Data_Package)); // Send the struct as a whole
  delay(10);
}

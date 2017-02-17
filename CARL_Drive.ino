//Servo power is from the AA pack
//Arduino power is frome the 9V
//Common ground required between the battery systems

//Servos data pin is connected to D2 and D3
//Bluetooth is getting 3.3v power from the arduino, TX and RX connect to the RX and TX of the arduino microcontroller
//NOTE: to upload code you must remove the bluetooth with this setup

#include <Servo.h>
#include <SoftwareSerial.h>
#include <DiodeControl.h>

Servo myservo1;
Servo myservo2;

//Sets up pins 4 and 5 to be used for serial communication (optional, not used in default configuration)
SoftwareSerial softSerial(5, 4); // RX, TX

char input = 'S';

void setup() {
  //Setup serial connections for Monitor and Bluetooth
  softSerial.begin(9600);
  Serial.begin(9600);

  //Connects to the servos
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);

  myservo1.attach(2);
  myservo2.attach(3);

  Serial.println("Setup Complete!");
}

void robotForward (int duration) {
  myservo1.write(45);
  myservo2.write(135);
}

void robotBackward (int duration) {
  myservo1.write(135);
  myservo2.write(45);
}

void robotRight (int duration) {
  myservo1.write(135);
  myservo2.write(135);
}

void robotLeft (int duration) {
  myservo1.write(45);
  myservo2.write(45);
}
void robotStop (int duration) {
  myservo1.write(90);
  myservo2.write(90);
}

void loop() {
  if (Serial.available())
  { //if there is data being recieved
    input = Serial.read();
    if (input == 'B')
    {
      robotBackward(1);
    }
    if (input == 'F')
    {
      robotForward(1);
    }
    if (input == 'R')
    {
      robotRight(1);
    }
    if (input == 'L')
    {
      robotLeft(1);
    }
    if (input == 'S' )
    {
      robotStop(1);
    }
  }
}



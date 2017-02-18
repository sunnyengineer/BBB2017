//Servo power is from the AA pack
//Arduino power is frome the 9V
//Common ground required between the battery systems

//Servos data pin is connected to D2 and D3
//Bluetooth is getting 3.3v power from the arduino, TX and RX connect to the RX and TX of the arduino microcontroller
//NOTE: to upload code you must remove the bluetooth with this setup

#include <Servo.h>
#include <SoftwareSerial.h>
 
int redPin = 5;
int greenPin = 6;
int bluePin = 7;
 
//uncomment this line if using a Common Anode LED
#define COMMON_ANODE

Servo myservo1;
Servo myservo2;
Servo spikeServo;

int diodeColor = 0;
int wedgePosition = 0;

//Sets up pins 4 and 5 to be used for serial communication (optional, not used in default configuration)
SoftwareSerial softSerial(5, 4); // RX, TX

char input = 'S';

void setup() {
  
  //Setup serial connections for Monitor and Bluetooth
  softSerial.begin(9600);
  Serial.begin(9600);
  Serial.println("Serial online!");

  //Connects to the servos
  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  // Connects the LEDs
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  

  myservo1.attach(2);
  myservo2.attach(3);
  spikeServo.attach(4);

  Serial.println("Setup Complete!");
}
/*void setHighLow(int color) {
  if(color == 0){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  }
  else if(color == 1){
    digitalWrite(redPin, HIGH);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, LOW);
  }
  else if(color == 2){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, HIGH);
    digitalWrite(bluePin, HIGH);
  }
  else if(color == 3){
    digitalWrite(redPin, LOW);
    digitalWrite(greenPin, LOW);
    digitalWrite(bluePin, HIGH);
  }
}*/
void setColor(int red, int green, int blue){
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  digitalWrite(redPin, red);
  digitalWrite(greenPin, green);
  digitalWrite(bluePin, blue);  
}

void robotForward (int duration) {
  myservo2.write(45);
  myservo1.write(135);
}

void robotBackward (int duration) {
  myservo2.write(135);
  myservo1.write(45);
}

void robotRight (int duration) {
  myservo2.write(135);
  myservo1.write(135);
}

void robotLeft (int duration) {
  myservo2.write(45);
  myservo1.write(45);
}
void robotStop (int duration) {
  myservo1.write(90);
  myservo2.write(90);
}

void spikeDown (int duration) {
  spikeServo.write(135);
  Serial.println("Spike Down");
}

void spikeUp (int duration) {
  spikeServo.write(45);
  Serial.println("Spike Up");
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
    if (input == 'W' || input == 'w') // Maps to "front lights on/off" in app
    {
       
        if(diodeColor == 0) { // white
          setColor(255, 0, 0);
          //setHighLow(1)
          diodeColor = 1;
        } else if (diodeColor == 1) { // red
          setColor(0, 255, 0);
          //setHighLow(2);
          diodeColor = 2;
        } else if (diodeColor == 2) { // green
          setColor(0, 0, 255);
          //setHighLow(3);
          diodeColor = 3;
        } else if (diodeColor == 3) { // blue
          setColor(255, 255, 255);
          //setHighLow(0);
          diodeColor = 0;
        }
    }
    
    if (input == 'U' || input == 'u') // Maps to "back lights on/off" in app
    {
      spikeDown(1);
    }

    if (input == 'V' || input == 'v') // Maps to "back lights on/off" in app
    {
      spikeUp(1);
    }
  }
}


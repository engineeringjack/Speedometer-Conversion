//Includes the Arduino Stepper Library
#include <Stepper.h>;
#include <Servo.h>  // Include the Servo library
Servo myServo;  // Create a Servo object
// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

int hall_pin = 2;
//

double rpmToSpeed = 0.1037556814;

//
int angle = 180;  // Variable to store the current servo position (initially unset)
int mph = 0;
int total = 0;
String input;
double odmMult = 6.9;
long waitTime;
long endTime;
int hallLast;
int hallNow;
int hallCnt;
int rpm;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence

Stepper myStepper = Stepper(stepsPerRevolution, 6, 8, 5, 7);

int calc(int mph){
  if (mph <= 10){
    mph = mph + 1;
  }
  return int(180-((mph)*(1.352)-8.5));
}

void setup() {
  Serial.begin(9600);  // Start serial communication
  myServo.attach(3);   // Attach the servo to pin 9
  // Don't move the servo until a valid angle is received
  myServo.write(calc(0));
  delay(300);
  for (int x=0; x < 130; x++){
    myServo.write(calc(x));
    delay(10);
  }
  myServo.write(calc(0));
  delay(300);
  pinMode(hall_pin, INPUT);
}



void loop() {
  // Check if there is incoming serial data
  //if (Serial.available() > 0) {
   // mph = Serial.readString().toInt();
   // Serial.println("REQUESTED MPH:" + mph);
    
  //}
  mph = rpm*rpmToSpeed;
  myServo.write(calc(mph));
  myStepper.setSpeed(15);
	myStepper.step(int(mph*odmMult*0.5));
  //Serial.println("MPH Reported: " + String(mph));
  //Serial.println("STM COUNT:" + String(mph*odmMult));
  if (mph != 0) {
    waitTime = (500-(mph*odmMult/2038*500));
    endTime = millis() + waitTime;
    hallLast = 0;
    hallCnt=-1;
    while (millis() < endTime){
      hallNow = digitalRead(hall_pin);
      
      if (hallNow != hallLast) {
        hallCnt += 1;
        //Serial.println("Hall Count: " + String(hallCnt));
      }
      hallLast = hallNow;
    }
    rpm = hallCnt*(500/waitTime);
    //Serial.println("RPM Calc: " + String(rpm));
  } else {
    waitTime = 500;
    endTime = millis() + waitTime;
    hallLast = 0;
    hallCnt=-1;
    while (millis() < endTime){
      hallNow = digitalRead(hall_pin);
      
      if (hallNow != hallLast) {
        hallCnt += 1;
        //Serial.println("Hall Count: " + String(hallCnt));
      }
      hallLast = hallNow;
    }
    rpm = hallCnt*(500/waitTime);
    //Serial.println("RPM Calc: " + String(rpm));
  }
}

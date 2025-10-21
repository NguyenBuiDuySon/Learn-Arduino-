#include <Servo.h>
#include <NewPing.h>

// Định nghĩa chân
#define trig_pin 7
#define echo_pin 4
#define max_distance 200

const int LeftMotorForward = 13;
const int LeftMotorBackward = 12;
const int RightMotorForward = 11;
const int RightMotorBackward = 10;
const int ena = 6;
const int enb = 5;

Servo servo_motor;
NewPing sonar(trig_pin, echo_pin, max_distance);

boolean goesForward = false;
int distance = 100;

void setup() {
  Serial.begin(9600);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
  
  servo_motor.attach(9);
  servo_motor.write(90);
  delay(1000);
}

void loop() {
  distance = readPing();

  if (distance <= 20) {
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    
    int distanceRight = lookRight();
    delay(300);
    int distanceLeft = lookLeft();
    delay(300);

    if (distanceRight >= distanceLeft) turnRight();
    else turnLeft();
  } 
  else moveForward();
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) cm = 250;
  return cm;
}

int lookRight() {
  servo_motor.write(30);
  delay(500);
  int d = readPing();
  servo_motor.write(90);
  return d;
}

int lookLeft() {
  servo_motor.write(150);
  delay(500);
  int d = readPing();
  servo_motor.write(90);
  return d;
}

void moveForward() {
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward() {
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
}

void turnRight() {
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(400);
}

void turnLeft() {
  analogWrite(ena, 200);
  analogWrite(enb, 200);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  delay(400);
}

void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

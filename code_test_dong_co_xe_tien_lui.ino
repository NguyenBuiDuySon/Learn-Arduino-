// Test motor L298N – chỉ chạy tiến và lùi
const int LeftMotorForward  = 13;
const int LeftMotorBackward = 12;
const int RightMotorForward = 11;
const int RightMotorBackward = 10;
const int ena = 6;
const int enb = 5;

void setup() {
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);

  // bật PWM ở mức 200/255 để động cơ chạy ổn định
  analogWrite(ena, 200);
  analogWrite(enb, 200);
}

void loop() {
  // chạy thẳng 2 giây
  moveForward();
  delay(5000);

  // dừng 1 giây
  moveStop();
  delay(1000);

  // lùi 2 giây
  moveBackward();
  delay(5000);

  // dừng 1 giây rồi lặp lại
  moveStop();
  delay(1000);
}

void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

void moveBackward() {
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
}

void moveStop() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}

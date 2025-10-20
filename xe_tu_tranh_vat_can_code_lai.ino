// Khai báo thư viện 
#include<Servo.h> // thu vien cua servo
#include<NewPing.h> // thu vien giup dieu khien toc do

// định nghĩa chân 
#define trig_pin 7 // gán chân 7 trên arduino làm chân trigger(phát xung) của cảm biến hc-sro4
#define echo_pin 4 // gán chân 4 trên arduino làm chân echo nhận xung phản hồi từ cảm biến
#define max_distance 200 // giới hạn khoản cách đo tối đa là 200cm tránh nhiễu ( tối đa 400)

/* khai báo chân
khai báo số chân digital arduino làm điều hướng quay của  module L298N
2 động cơ độc lập rẽ trái và phải nên khai báo mỗi bánh 2 chân*/ 
const int LeftForward = 13; 
const int LeftBackward = 12;
const int RightForward = 11;
const int RightBackward = 10;
/*điều khiển tốc độ động cơ 
sử dụng analogWrite() */
const int ena = 6; // chân D6 của arduino 
const int enb = 5; // chân D5 của arduino

// Khai báo đối tượng servor
Servo servo_motor;
NewPing sonar(trig_pin,echo_pin,max_distance); // khai báo giá trị cho NewPing

//Khai báo trạng thái của xe
boolean goesForward = false // dùng để ghi nhận trạng thái xe, dừng, lùi = false, tới = true
int distance = 100 // khoảng cách mặt định đo ban đầu 
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

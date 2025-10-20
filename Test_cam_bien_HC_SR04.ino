// Test cảm biến HC-SR04 ổn định
#define trigPin 9
#define echoPin 10

long duration;
float distance;
float distance_avg;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("Kiem tra cam bien HC-SR04...");
}

void loop() {
  // Gửi xung trigger 10 micro giây
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Đo thời gian echo phản hồi
  duration = pulseIn(echoPin, HIGH, 25000); // giới hạn 25 ms (~4m)
  
  // Nếu không có phản hồi (duration = 0), bỏ qua để tránh nhiễu
  if (duration == 0) {
    Serial.println("Ngoai tam hoac khong nhan duoc song.");
    delay(500);
    return;
  }

  // Tính khoảng cách (cm)
  distance = duration * 0.0343 / 2;

  // Lọc nhiễu bằng trung bình 3 lần đo liên tiếp
  static float prev1 = 0, prev2 = 0;
  distance_avg = (distance + prev1 + prev2) / 3.0;
  prev2 = prev1;
  prev1 = distance;

  // In ra Serial Monitor
  Serial.print("Khoang cach: ");
  Serial.print(distance_avg, 1);
  Serial.println(" cm");

  delay(300);
}

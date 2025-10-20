// Test cảm biến HC-SR04 có LED cảnh báo
#define trigPin 9
#define echoPin 10
#define ledPin 7  // LED cảnh báo

long duration;
float distance;
float distance_avg;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("Kiem tra cam bien HC-SR04 + LED bao vat can...");
}

void loop() {
  // Phát xung trigger 10 micro giây
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Đo thời gian echo phản hồi, giới hạn 25ms (~4m)
  duration = pulseIn(echoPin, HIGH, 25000);

  // Nếu không có phản hồi
  if (duration == 0) {
    Serial.println("Ngoai tam hoac khong nhan duoc song.");
    digitalWrite(ledPin, LOW);
    delay(500);
    return;
  }

  // Tính khoảng cách (cm)
  distance = duration * 0.00343 / 2;

  // Lọc nhiễu bằng trung bình 3 lần đo
  static float prev1 = 0, prev2 = 0;
  distance_avg = (distance + prev1 + prev2) / 3.0;
  prev2 = prev1;
  prev1 = distance;

  // In ra Serial Monitor
  Serial.print("Khoang cach: ");
  Serial.print(distance_avg, 1);
  Serial.println(" cm");

  // Bật LED nếu vật ở gần hơn 10 cm
  if (distance_avg <= 10.0) digitalWrite(ledPin, HIGH);
  else digitalWrite(ledPin, LOW);

  delay(300);
}

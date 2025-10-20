#define TRIG 9
#define ECHO 10
#define TIMEOUT 25000   // 25 ms tương đương ~4m
float CAL = 1.0;        // hệ số hiệu chỉnh (điều chỉnh nếu lệch cm)

// ---------- HÀM ĐO CẢM BIẾN ----------

// Đo thời gian phản hồi sóng siêu âm (micro giây)
long measureRaw() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long d = pulseIn(ECHO, HIGH, TIMEOUT); // micro giây
  return d; // 0 nếu timeout
}

// Tính khoảng cách trung bình (lọc median)
float measureCm() {
  const int N = 5;  // số lần đo mỗi chu kỳ
  long arr[N];
  for (int i = 0; i < N; i++) {
    arr[i] = measureRaw();
    delay(30);
  }

  // Sắp xếp mảng để lấy giá trị trung vị (median)
  for (int i = 0; i < N - 1; i++) {
    for (int j = i + 1; j < N; j++) {
      if (arr[j] < arr[i]) {
        long t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
      }
    }
  }

  long med = arr[N / 2];
  if (med == 0) return -1; // không nhận được sóng

  // chuyển sang cm (tốc độ âm 0.0343 cm/µs), chia 2 (đi & về), nhân hệ số hiệu chỉnh
  float cm = (med * 0.0343f / 2.0f) * CAL;

  // loại bỏ các giá trị vô lý
  if (cm > 400 || cm < 1) return -1;
  return cm;
}

// ---------- CHƯƠNG TRÌNH CHÍNH ----------

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.println("Bat dau kiem tra cam bien HC-SR04 on dinh...");
}

void loop() {
  float d = measureCm();

  if (d < 0) {
    Serial.println("Ngoai tam hoac khong nhan duoc song.");
  } else {
    Serial.print("Khoang cach: ");
    Serial.print(d, 1);
    Serial.println(" cm");
  }

  delay(500);
}

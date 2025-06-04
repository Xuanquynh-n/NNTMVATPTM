#define PIR_PIN 2
#define RELAY_SIGNAL 3
#define RELAY_LIGHT 4

unsigned long lastTriggerTime = 0;
bool active = false;

void setup() {
  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_SIGNAL, OUTPUT);
  pinMode(RELAY_LIGHT, OUTPUT);
  digitalWrite(RELAY_SIGNAL, LOW);
  digitalWrite(RELAY_LIGHT, LOW);
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(PIR_PIN);

  // Nếu phát hiện có người và hệ thống đang ở trạng thái chờ
  if (motion == HIGH && !active) {
    Serial.println("🚶 Có người – kích hoạt đèn trong 10 giây");
    digitalWrite(RELAY_SIGNAL, HIGH);
    digitalWrite(RELAY_LIGHT, HIGH);
    lastTriggerTime = millis();
    active = true;
  }

  // Sau 10 giây → tắt relay và cho phép kích hoạt lại
  if (active && millis() - lastTriggerTime >= 10000) {
    Serial.println("⏲️ Đã hết 10 giây – tắt đèn");
    digitalWrite(RELAY_SIGNAL, LOW);
    digitalWrite(RELAY_LIGHT, LOW);
    active = false;
  }

  delay(100); // chống nhiễu nhẹ
}

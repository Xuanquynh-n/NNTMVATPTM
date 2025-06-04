# 🚦 Hệ Thống Hỗ Trợ Qua Đường Cho Người Đi Bộ (Arduino + PIR + Relay)

## 📌 Giới thiệu

Dự án mô phỏng một hệ thống thông minh giúp người đi bộ qua đường an toàn hơn, đặc biệt trong điều kiện thiếu sáng hoặc không có đèn giao thông.  
Hệ thống sử dụng:

- ✅ Cảm biến hồng ngoại PIR để phát hiện người đứng trước vạch qua đường
- ✅ Hai relay điều khiển:
  - Đèn tín hiệu cảnh báo phương tiện
  - Đèn chiếu sáng vạch đường cho người đi bộ
- ✅ Tự động bật đèn trong 10 giây khi phát hiện người, sau đó tắt và sẵn sàng chu kỳ mới.

---

## 🎯 Mục tiêu hoạt động

1. Khi cảm biến PIR phát hiện người:
   - Đèn **tín hiệu** (gắn relay 1) sáng để cảnh báo phương tiện
   - Đèn **chiếu sáng** (gắn relay 2) bật để hỗ trợ người đi bộ
2. Cả hai đèn **sáng trong 10 giây**, rồi tự động tắt
3. Hệ thống chống phát hiện lại liên tục khi có nhiều người – đảm bảo **mỗi lần kích hoạt cách nhau ít nhất 10 giây**

---

## 🧰 Phần cứng sử dụng

| Thiết bị                | Ghi chú |
|-------------------------|--------|
| Arduino Uno             | Điều khiển trung tâm |
| Cảm biến PIR HC-SR501   | Phát hiện người đi bộ |
| 2 Relay 1 kênh (5V)      | Điều khiển đèn tín hiệu & chiếu sáng |
| 2 đèn LED (5V hoặc 12V) | Mô phỏng đèn tín hiệu & đèn chiếu sáng |
| Breadboard + dây nối    | Lắp ráp mạch |

---

## 🔌 Sơ đồ nối chân

| Thành phần | Arduino | Ghi chú |
|------------|---------|--------|
| PIR - OUT  | D2      | Phát hiện người |
| Relay 1 - IN | D3    | Điều khiển đèn tín hiệu |
| Relay 2 - IN | D4    | Điều khiển đèn chiếu sáng |
| Các VCC     | 5V     | Có thể cần nguồn ngoài nếu relay yếu |
| Các GND     | GND    | GND phải nối chung tất cả thiết bị |

---

## 💡 Code chính

```cpp
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

  if (motion == HIGH && !active) {
    Serial.println("🚶 Có người – bật đèn");
    digitalWrite(RELAY_SIGNAL, HIGH);
    digitalWrite(RELAY_LIGHT, HIGH);
    lastTriggerTime = millis();
    active = true;
  }

  if (active && millis() - lastTriggerTime >= 10000) {
    Serial.println("⏲️ Tắt đèn sau 10 giây");
    digitalWrite(RELAY_SIGNAL, LOW);
    digitalWrite(RELAY_LIGHT, LOW);
    active = false;
  }

  delay(100);
}

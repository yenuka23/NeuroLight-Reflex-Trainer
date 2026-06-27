#include <esp_now.h>
#include <WiFi.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define LED1_PIN 4
#define LED2_PIN 5
#define LED3_PIN 6

uint8_t active = 0;  // Only light up when this is set

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len == 1) {
    active = data[0];
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}

float getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);  // Timeout 30ms
  return duration * 0.034 / 2;
}

void loop() {
  if (active) {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED3_PIN, HIGH);

    float distance = getDistanceCM();
    if (distance > 0 && distance < 10) {
      active = 0;
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);
      digitalWrite(LED3_PIN, LOW);
    }
  }
}

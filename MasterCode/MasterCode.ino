#include <esp_now.h>
#include <WiFi.h>

uint8_t clients[][6] = {
  {0xD8, 0x3B, 0xDA, 0x27, 0x8D, 0xD4},  // Board 1
  {0xD8, 0x3B, 0xDA, 0x27, 0xAA, 0x10},  // Board 2
  {0x84, 0xF7, 0x03, 0x09, 0xFB, 0x64}   // Board 4
};

int currentIndex = -1;
bool waiting = false;
unsigned long lastSend = 0;
const int maxWait = 700;  // Max wait time before skipping if no hand detected

void onDataRecv(const esp_now_recv_info_t *info, const uint8_t *data, int len) {
  if (len == 1 && data[0] == 0) {
    waiting = false;
  }
}

void sendToClient(int index, uint8_t value) {
  esp_now_send(clients[index], &value, sizeof(value));
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);

  for (int i = 0; i < 3; i++) {
    esp_now_peer_info_t peer = {};
    memcpy(peer.peer_addr, clients[i], 6);
    peer.channel = 0;
    peer.encrypt = false;

    if (!esp_now_is_peer_exist(clients[i])) {
      esp_now_add_peer(&peer);
    }
  }
}

void loop() {
  unsigned long now = millis();

  if (!waiting) {
    // Pick a new client different from the last one
    int nextIndex;
    do {
      nextIndex = random(0, 3);
    } while (nextIndex == currentIndex);

    currentIndex = nextIndex;
    sendToClient(currentIndex, 1);
    waiting = true;
    lastSend = now;
  }

  // If hand not detected in time, move on
  if (waiting && (millis() - lastSend > maxWait)) {
    waiting = false;
  }
}

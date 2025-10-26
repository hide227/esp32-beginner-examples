#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.begin("ssid", "key");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Wi-Fi Connected");
}

void loop() {
}

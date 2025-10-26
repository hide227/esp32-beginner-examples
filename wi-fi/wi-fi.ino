#include <WiFi.h>

char* ssid = "ssid";
char* key = "key";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, key);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Wi-Fi Connected");
}

void showRssi() {
  Serial.print("RSSI: ");
  long rssi = WiFi.RSSI();
  Serial.println(rssi);
}


void loop() {
  showRssi();
  delay(1000);
}

// Wi-Fi client
#include <WiFi.h>

// LCD Display
// Reference: https://docs.sunfounder.com/projects/esp32-starter-kit/en/latest/arduino/basic_projects/ar_lcd.html
#include <Wire.h>
// required to install the LiquidCrystal I2C library from the Library Manager
#include <LiquidCrystal_I2C.h>

char* ssid = "ssid";
char* key = "key";

// SDA->21, SCL->22
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27
                                    // for a 16 chars and 2 line display
int count = 0;

void setup() {
  // connect Wi-Fi AP
  Serial.begin(115200);
  WiFi.begin(ssid, key);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println("Wi-Fi Connected");

  // setup lcd display
  lcd.init();       // initialize the lcd
  lcd.backlight();  // turns on the LCD backlight.
  delay(3000);
}

void showRssi() {
  long rssi = WiFi.RSSI();
  Serial.println(rssi);
  lcd.setCursor(0, 0);
  lcd.print("Signal Strength"); // print a message to the LCD

  lcd.setCursor(0, 1);  // sets the cursor position to the
                        // second row and first column (0, 1)
  lcd.print("RSSI: ");
  lcd.print(rssi);
  lcd.print("dBm");
}


void loop() {
  lcd.clear();
  showRssi();
  delay(1000);
}

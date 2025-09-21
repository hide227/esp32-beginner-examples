const int gpioPin = 5;
const int baudrate = 115200;
const int interval = 500;   // 500ms

void setup() {
  pinMode(gpioPin, OUTPUT);
  Serial.begin(baudrate);
  Serial.println("Ready");
}

void loop() {
  digitalWrite(gpioPin, HIGH);
  Serial.println("LED ON");
  delay(interval);
  digitalWrite(gpioPin, LOW);
  Serial.println("LED OFF");
  delay(interval);
}

void setup() {
  pinMode(5, OUTPUT);
  Serial.begin(115200);
  Serial.println("Ready");
}

void loop() {
  digitalWrite(5, HIGH);
  Serial.println("LED ON");
  delay(1000);
  digitalWrite(5, LOW);
  Serial.println("LED OFF");
  delay(1000);
}

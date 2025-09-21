const int gpioPin = 5;          // The GPIO pin number where the LED is connected (in this case, GPIO 5)
int brightness = 0;             // The current brightness level of the LED (initially set to 0)
int fadeAmount = 8;             // The amount by which the LED's brightness will change in each step
const int interval = 50;        // Wait 50 milliseconds in each loop

// LEDC (LED Control) params
const int freq = 5000;          // Frequency of pwm
const int resolutionBits = 8;   // Resolution for ledc channel. 1-20 bits for ESP32

void setup() {
  ledcAttach(gpioPin, freq, resolutionBits);   // Attach the LED pin
}

void loop() {
  ledcWrite(gpioPin, brightness);   // Write the new brightness value to the PWM pin
  brightness = brightness + fadeAmount;
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  delay(50);  // Wait for 50 milliseconds
}

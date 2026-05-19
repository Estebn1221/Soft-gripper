#include <Servo.h>

Servo myServo;

const int   potPin          = A0;
const float HYSTERESIS      = 2.5;  // degrees — raise if servo jitters at zone edges
const int   SAMPLE_INTERVAL = 15;   // ms — how often to read the pot (replaces delay)

int      lastAngle  = -1;
uint32_t lastSample = 0;

void setup() {
  myServo.attach(9);
  myServo.write(0);
}

void loop() {
  uint32_t now = millis();

  // Only sample the pot every SAMPLE_INTERVAL ms — non-blocking, no delay()
  if (now - lastSample < SAMPLE_INTERVAL) return;
  lastSample = now;

  int val = analogRead(potPin);

  // Map ADC [0,1023] → potentiometer physical angle [0°,270°]
  float potAngle = val * (270.0 / 1023.0);

  // Zone logic with hysteresis at each boundary
  int targetAngle;
  if      (potAngle < 45  - (lastAngle > 60  ? 0 : HYSTERESIS)) targetAngle = 60;
  else if (potAngle < 90  - (lastAngle > 120 ? 0 : HYSTERESIS)) targetAngle = 120;
  else if (potAngle < 135 - (lastAngle > 180 ? 0 : HYSTERESIS)) targetAngle = 180;
  else                                                            targetAngle = 0;

  // Only write to servo if the target changed — avoids micro-jitter
  if (targetAngle != lastAngle) {
    myServo.write(targetAngle);
    lastAngle = targetAngle;
  }
}

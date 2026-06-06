#include <Servo.h>
Servo myServo;

const int STEP_INTERVAL = 20;  // ms per 1° step — increase to slow down
const int potPin = A1;

int targetAngle = 0;
int currentAngle = 0;  // tracks actual servo position
int lastAngle = -1;  // track last written angle
int val = 0;
uint32_t lastStep = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(12);
  myServo.write(0);
}

void loop() {
  val = analogRead(potPin);
  float potAngle = val * (180.0 / 1023.0);

  if (potAngle < 40) targetAngle = 0;
  else if (potAngle > 40 && potAngle <= 80) targetAngle = 60;
  else if (potAngle > 80 && potAngle <= 120) targetAngle = 120;
  else if (potAngle > 120) targetAngle = 179;

 if (millis() - lastStep >= STEP_INTERVAL) {
    lastStep = millis();

    if (currentAngle < targetAngle) {
      currentAngle++;
      myServo.write(currentAngle);
    } else if (currentAngle > targetAngle) {
      currentAngle--;
      myServo.write(currentAngle);
    }
  }
}
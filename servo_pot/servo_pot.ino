#include <Servo.h>
Servo myServo;

const int potPin = A1;
int targetAngle = 0;
int lastAngle = -1;  // track last written angle
int val = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(10);
  myServo.write(0);
}

void loop() {
  val = analogRead(potPin);
  float potAngle = val * (180.0 / 1023.0);

  if (potAngle < 40) targetAngle = 0;
  else if (potAngle > 40 && potAngle <= 80) targetAngle = 60;
  else if (potAngle > 80 && potAngle <= 120) targetAngle = 120;
  else if (potAngle > 120) targetAngle = 180;

  // Only write when zone actually changed
  if (targetAngle != lastAngle) {
    myServo.write(targetAngle);
    lastAngle = targetAngle;
    Serial.print("Change of angle");
  }

  Serial.print(potAngle);
  Serial.print("...");
  Serial.println(targetAngle);

  delay(100);
}
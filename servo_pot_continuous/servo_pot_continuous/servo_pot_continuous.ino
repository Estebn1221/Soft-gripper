#include <Servo.h>

Servo myServo;

const int potPin = A1;
int val = 0;
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(10);
  myServo.write(0);
}

void loop() {
  // Read the potentiometer value (0 - 1023)
  val = analogRead(potPin);
  angle = map(val, 0, 1023, 0, 180);  // Map the value

  // Set the servo position
  myServo.write(angle);

  Serial.print(angle);
  Serial.print("...");
  Serial.println(val);

  // delay
  delay(15);
}

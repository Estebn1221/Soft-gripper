#include <Servo.h>

Servo myServo;

// ─── PINS ────────────────────────────────────────────────────────────────────
const int PIN_SERVO      = 9;
const int PIN_BTN_CLOSE  = 7;   // Hold to close gripper / release to return
const int PIN_BTN_HOLD   = 8;   // Press to save current angle as return target

// ─── MOVEMENT TUNING ─────────────────────────────────────────────────────────
const int   SERVO_MIN       = 0;    // degrees — fully open
const int   SERVO_MAX       = 170;  // degrees — max close (stay off hard limit)
const int   STEP_DEG        = 1;    // degrees moved per tick
const int   STEP_INTERVAL   = 20;   // ms per step → 1°/20ms as requested

// ─── STATE ───────────────────────────────────────────────────────────────────
int      currentAngle  = SERVO_MIN;  // live servo position
int      returnTarget  = SERVO_MIN;  // angle Button 2 saves; servo returns here on release

uint32_t lastStep      = 0;          // millis() timestamp of last movement tick

// Button 2 debounce
bool     lastBtn2State = HIGH;

void setup() {
  myServo.attach(PIN_SERVO);
  myServo.write(currentAngle);

  // INPUT_PULLUP: buttons connect pin to GND when pressed (no external resistor needed)
  pinMode(PIN_BTN_CLOSE, INPUT_PULLUP);
  pinMode(PIN_BTN_HOLD,  INPUT_PULLUP);
}

void loop() {
  uint32_t now = millis();

  // ── Button 2: save current angle as return target (on press edge only) ─────
  bool btn2State = digitalRead(PIN_BTN_HOLD);
  if (btn2State == LOW && lastBtn2State == HIGH) {
    // Falling edge = button just pressed → snapshot current position
    returnTarget = currentAngle;
  }
  lastBtn2State = btn2State;

  // ── Movement tick (runs at STEP_INTERVAL regardless of which direction) ────
  if (now - lastStep < STEP_INTERVAL) return;
  lastStep = now;

  bool closing = (digitalRead(PIN_BTN_CLOSE) == LOW);  // LOW = pressed

  if (closing) {
    // Button 1 held: move toward SERVO_MAX one step at a time
    if (currentAngle < SERVO_MAX) {
      currentAngle++;
      myServo.write(currentAngle);
    }
  } else {
    // Button 1 released: gradually return to returnTarget at the same speed
    if (currentAngle > returnTarget) {
      currentAngle--;
      myServo.write(currentAngle);
    } else if (currentAngle < returnTarget) {
      currentAngle++;
      myServo.write(currentAngle);
    }
    // If currentAngle == returnTarget: servo is already at rest, no write needed
  }
}

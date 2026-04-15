#include <Servo.h>
Servo servo1;
int servoPin = 8;
int button1 = 0;
int button2 = 0;

void setup() {
  Serial.monitor(9600);
  servo1.attach(servoPin);
  servo1.write(0);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
}

void loop () {
  button1 = digitalRead(A0);
  button2 = digitalRead(A1);
  Serial.print(button1)
  if(button1 == HIGH){
    i++;
    servo1.writte(i);
    delay(10);    
  }
  else if(button2 == HIGH){
    i--;
    servo1.writte(i);
    delay(10);
  }
  }
}
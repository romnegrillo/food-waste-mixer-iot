const int actuatorPWMPin1 = A5;
const int actuatorPWMPin2 = A0;
const int actuatorDirPin11 = A4;
const int actuatorDirPin12 = A3;
const int actuatorDirPin21 = A2;
const int actuatorDirPin22 = A1;
const int motorSpeed = 255;

void stopActuator1() {
  analogWrite(actuatorPWMPin1, 0);
}

void stopActuator2() {
  analogWrite(actuatorPWMPin2, 0);
}

void forwardActuator1() {
  digitalWrite(actuatorDirPin11, HIGH);
  digitalWrite(actuatorDirPin12, LOW);
  analogWrite(actuatorPWMPin1, motorSpeed);
}

void forwardActuator2() {
  digitalWrite(actuatorDirPin21, HIGH);
  digitalWrite(actuatorDirPin22, LOW);
  analogWrite(actuatorPWMPin2, motorSpeed);
}

void backwardActuator1() {
  digitalWrite(actuatorDirPin11, LOW);
  digitalWrite(actuatorDirPin12, HIGH);
  analogWrite(actuatorPWMPin1, motorSpeed);
}

void backwardActuator2() {
  digitalWrite(actuatorDirPin21, LOW);
  digitalWrite(actuatorDirPin22, HIGH);
  analogWrite(actuatorPWMPin2, motorSpeed);
}

void setup() {
  pinMode(actuatorPWMPin1, OUTPUT);
  pinMode(actuatorPWMPin2, OUTPUT);
  pinMode(actuatorDirPin11, OUTPUT);
  pinMode(actuatorDirPin12, OUTPUT);
  pinMode(actuatorDirPin21, OUTPUT);
  pinMode(actuatorDirPin22, OUTPUT);
}

void loop() {
  forwardActuator1();
  delay(3000);
  backwardActuator1();
  delay(3000);
  forwardActuator2();
  delay(3000);
  backwardActuator2();
  delay(3000);
}

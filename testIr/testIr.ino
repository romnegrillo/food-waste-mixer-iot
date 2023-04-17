const int irPin1 = 6;
const int irPin2 = 7;

void setup() {
  Serial.begin(115200);
  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);
}

void loop() {
  // '!' is placed because the sensor has inverse logic.
  Serial.println("IR 1 status: " + String(!digitalRead(irPin1)));
  Serial.println("IR 2 status: " + String(!digitalRead(irPin2)));

  delay(1000);
}

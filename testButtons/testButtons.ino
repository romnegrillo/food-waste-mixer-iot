const int buttonPin1 = 4;
const int buttonPin2 = 5;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
}

void loop() {
  // '!' is placed because the buttons is pulled up.
  Serial.println("Button 1 status: " + String(!digitalRead(buttonPin1)));
  Serial.println("Button 2 status: " + String(!digitalRead(buttonPin2)));

  delay(1000);
}

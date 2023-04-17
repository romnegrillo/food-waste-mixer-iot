const int relayPin1 = 8;
const int relayPin2 = 9;

void setup() {
  Serial.begin(115200);
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
}

void loop() {
  // '!' is placed because the relay has inverse logic.
  Serial.println("Relays turned on.");
  digitalWrite(relayPin1, !HIGH);
  digitalWrite(relayPin2, !HIGH);
  delay(3000);
  
  Serial.println("Relays turned off.");
  digitalWrite(relayPin1, !LOW);
  digitalWrite(relayPin2, !LOW);
  delay(3000);
}

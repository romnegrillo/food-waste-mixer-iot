#include <SoftwareSerial.h>

// Button pin definitions for
// manual on-off of the locks.
const int buttonPin1 = 4;
const int buttonPin2 = 5;

// IR pin definitions.
const int irPin1 = 6;
const int irPin2 = 7;

// Relay pin definitions for the motor.
const int relayPin1 = 8;
const int relayPin2 = 9;

// L298N pin defintions for actuator locks.
const int actuatorPWMPin1 = 10; // Needs to be a tilde (~) pin.
const int actuatorPWMPin2 = 11; // Needs to be a tilde (~) pin.
const int actuatorDirPin11 = A0;
const int actuatorDirPin12 = A1;
const int actuatorDirPin21 = A2;
const int actuatorDirPin22 = A3;
const int motorSpeed = 255;

// Grinder time definitions.
const int grinderMaxOnTime = 10000;
int grinderCurrentTime = 0;


// Variable to check if the sequence already started.
bool isSequenceStarted = false;

// Status of sensors and actuators.
// Made it global as not everything it can be placed on loop() function,
// easier to track this way.
bool button1Status;
bool button2Status;
bool button3Status;

bool ir1Status;
bool ir2Status;

bool relay1Status;
bool relay2Status;

bool actuator1Status;
bool actuator2Status;

String inputString;

String message = "";
String prevMessage = "";

void forwardActuator1() {
  digitalWrite(actuatorDirPin11, HIGH);
  digitalWrite(actuatorDirPin12, LOW);
  analogWrite(actuatorPWMPin1, motorSpeed);

  actuator1Status = true;
}

void forwardActuator2() {
  digitalWrite(actuatorDirPin21, HIGH);
  digitalWrite(actuatorDirPin22, LOW);
  analogWrite(actuatorPWMPin2, motorSpeed);

  actuator2Status = true;
}

void backwardActuator1() {
  digitalWrite(actuatorDirPin11, LOW);
  digitalWrite(actuatorDirPin12, HIGH);
  analogWrite(actuatorPWMPin1, motorSpeed);

  actuator1Status = false;
}

void backwardActuator2() {
  digitalWrite(actuatorDirPin21, LOW);
  digitalWrite(actuatorDirPin22, HIGH);
  analogWrite(actuatorPWMPin2, motorSpeed);

  actuator2Status = false;
}

void turnOnRelay1() {
  // '!' is placed because the sensor has inverse logic.
  digitalWrite(relayPin1, !HIGH);

  relay1Status = true;
}

void  turnOffRelay1() {
  // '!' is placed because the sensor has inverse logic.
  digitalWrite(relayPin1, !LOW);

  relay1Status = false;
}

void turnOnRelay2() {
  // '!' is placed because the sensor has inverse logic.
  digitalWrite(relayPin2, !HIGH);

  relay2Status = true;
}

void turnOffRelay2() {
  // '!' is placed because the sensor has inverse logic.
  digitalWrite(relayPin2, !LOW);

  relay2Status = false;
}

void sendTextMessage(String message) {
  // TODO:
}

void setup() {
  Serial.begin(115200);
  Serial.flush();
 
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);

  pinMode(irPin1, INPUT);
  pinMode(irPin2, INPUT);

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);

  pinMode(actuatorPWMPin1, OUTPUT);
  pinMode(actuatorPWMPin2, OUTPUT);
  pinMode(actuatorDirPin11, OUTPUT);
  pinMode(actuatorDirPin12, OUTPUT);
  pinMode(actuatorDirPin21, OUTPUT);
  pinMode(actuatorDirPin22, OUTPUT);

  turnOffAllActuators();

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
}

void turnOffAllActuators() {
  turnOffRelay1();
  turnOffRelay2();
  backwardActuator1();
  backwardActuator2();
}

void readIncomingData() {
  if (Serial.available() > 0) {
    inputString = Serial.readStringUntil('\n');


    digitalWrite(13, HIGH);

    // Find the position of the equals sign in the string
    int equalsPos = inputString.indexOf("=");

    // Extract the variable name and value using substring()
    String variableName = inputString.substring(0, equalsPos);
    int variableValue = inputString.substring(equalsPos + 1).toInt();

    if (variableName == "relay1Status") {
      if (variableValue) {
        turnOnRelay1();
      } else {
        turnOffRelay1();
      }
    } else if (variableName == "relay2Status") {
      if (variableValue) {
        turnOnRelay2();
      } else {
        turnOffRelay2();
      }
    } else if (variableName == "actuator1Status") {
      if (variableValue) {
        forwardActuator1();
      } else {
        backwardActuator1();
      }
    } else if (variableName == "actuator2Status") {
      if (variableValue) {
        forwardActuator2();
      } else {
        backwardActuator2();
      }
    }

  }
}

void loop() {
  // '!' is placed because the buttons is pulled up.
  button1Status = !digitalRead(buttonPin1); // Soil lock manual button control.
  button2Status = !digitalRead(buttonPin2);  // Mixer lock manual button control.

  // '!' is placed because the sensor has inverse logic.
  ir1Status = !digitalRead(irPin1); // Grinder container IR.
  ir2Status = !digitalRead(irPin2); // Soil cointainer IR.

  // Only start the sequence if the IR 1 became active for the first time.
  if (ir1Status && !isSequenceStarted) {
    isSequenceStarted = true;
  }

  // If button3 is pressed, reset the sequence as a stop point.
  if (button3Status) {
    isSequenceStarted = false;
  }

  if (isSequenceStarted) {
    // TODO:
    // All logic on sequene.
    // 1.) If IR1 is high - completed at this point.
    // 2.) Open motor 1 (grinder motor).
    // 3.) After 10 mins, open lock 1 (soil container).
    // 4.) After 5 mins, open motor 2 (mixer motor).
    // 5.) Open motor lock 2 (mixer lock)
    // 6.) When the lock 2 mixer lock is opened,
    // check if IR2 is high then send GSM message.
  } else {
    // Reset.
    // Turn off all motor relays and actuators.
    turnOffAllActuators();
  }

  // Message to send in Node MCU composed of 0s and 1s only for status.
  // Ex: for the first 3 vaues, it's the button status
  // 000 -> all off.
  // 111 -> all on.
  // 010 -> button 2 is the only on.
  message = "";
  message += String(button1Status);
  message += String(button2Status);
  message += String(ir1Status);
  message += String(ir2Status);
  message += String(relay1Status);
  message += String(relay2Status);
  message += String(actuator1Status);
  message += String(actuator2Status);
  message += String(isSequenceStarted);

  readIncomingData();

  // Send data via serial.
  // Send only if the data has been updated from
  // change in user inpt or pinging the NodeMCU.
  
  if(message != prevMessage) {
    Serial.println(message);  
  }

  prevMessage = message;

  delay(500);
}

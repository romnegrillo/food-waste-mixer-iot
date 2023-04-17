#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

// Blynk constants.
#define BLYNK_TEMPLATE_ID           "TMPL66my35GP4"
#define BLYNK_TEMPLATE_NAME         "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "tJGNpagLU3PqFu-JkyOtQYHtr5oN-SBa"
#define BLYNK_PRINT Serial

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PLDTHOMEFIBRPMybC";
char pass[] = "PLDTWIFI3qgQ5";

BlynkTimer timer;

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  String toSend = String("relay1Status") + String("=") + String(value);
  Serial.println(toSend);
}

BLYNK_WRITE(V3)
{
  int value = param.asInt();  
  String toSend = String("relay2Status") + String("=") + String(value);
  Serial.println(toSend);
}

BLYNK_WRITE(V4)
{
  int value = param.asInt();
  String toSend = String("actuator1Status") + String("=") + String(value);
  Serial.println(toSend);
}

BLYNK_WRITE(V5)
{
  int value = param.asInt();
  String toSend = String("actuator2Status") + String("=") + String(value);
  Serial.println(toSend);
}

void myTimerEvent()
{
  // Runs every 1 seconds.
  // I didn't use this becase the data is dependent on serial
  // from the Arduino, I just added the delay on Arduino source.
}

void readIncomingData() {
  // Read formatted string data from Arduino.
  // Process will be handles on myTimerEvent.
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');

    char button1Status = inputString.charAt(0); // Not used, just added for consistency.
    char button2Status = inputString.charAt(1); // Not used, just added for consistency.
    char ir1Status = inputString.charAt(2);
    char ir2Status = inputString.charAt(3);
    char relay1Status = inputString.charAt(4);
    char relay2Status = inputString.charAt(5);
    char actuator1Status = inputString.charAt(6);
    char actuator2Status = inputString.charAt(7);
    char isSequenceStarted = inputString.charAt(8);

    if (ir1Status == '0') {
      Blynk.virtualWrite(V0, "OFF");
    } else {
      Blynk.virtualWrite(V0, "ON");
    }

    if (ir2Status == '0') {
      Blynk.virtualWrite(V1, "OFF");
    } else {
      Blynk.virtualWrite(V1, "ON");
    }

    if (relay1Status == '0') {
      Blynk.virtualWrite(V2, 0);
    } else {
      Blynk.virtualWrite(V2, 1);
    }

    if (relay2Status == '0') {
      Blynk.virtualWrite(V3, 0);
    } else {
      Blynk.virtualWrite(V3, 1);
    }

    if (actuator1Status == '0') {
      Blynk.virtualWrite(V4, 0);
    } else {
      Blynk.virtualWrite(V4, 1);
    }

    if (actuator2Status == '0') {
      Blynk.virtualWrite(V5, 0);
    } else {
      Blynk.virtualWrite(V5, 1);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.flush();
 
  // Initialize Blynk instance.
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Setup a function to be called every second.
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();

  readIncomingData();
}

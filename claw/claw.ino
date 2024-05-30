#include "controller.h"
#include <WiFi.h>

<<<<<<< HEAD
// Define the PWM pin for the servo
const int servoPin = 16;

// Define the open and close positions
const int openPosition = 255; // Adjust as needed
const int closePosition = 0; // Adjust as needed

int position = 0;

ControllerStream controller(0);

void setup()
{

    Serial.begin(115200);
    Serial.println("Initializing...");

    // Attach the servo to the PWM pin
    // myServo.attach(servoPin);
    pinMode(servoPin, OUTPUT);
    analogWrite(servoPin, 0);

    WiFi.mode(WIFI_STA);
    WiFi.begin("kyle-hotspot", "");
    WiFi.setOutputPower(20.5);
    // Initialize wifi connection
    int status = WiFi.waitForConnectResult();
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println("kyle-hotspot");
        WiFi.begin("kyle-hotspot");
        status = WiFi.waitForConnectResult();
        Serial.print("Status: ");
        Serial.println(status);
        // wait 2 seconds for connection:
        delay(2000);
    }
    wifi_set_sleep_type(NONE_SLEEP_T);
    Serial.println("Connected to WiFi.");
    printWiFiStatus();

    // Initialize the servo to the closed position
    // myServo.write(closePosition);

    // Optional: Add a small delay to allow the servo to reach the initial position
    delay(1000);
}

void loop()
{
    controller.updateData();
    ControllerData controllerData = controller.getControllerData();
    // Open the servo

    if (controllerData.getA())
    {
        Serial.println("Open claw.");
        position = openPosition;
    }
    else if (controllerData.getB())
    {
        Serial.println("Close claw.");
        position = closePosition;
    }
    else {
        Serial.println("No action.");
    }

    analogWrite(servoPin, position);
    delay(100);
=======
#include <Servo.h>

// Create a Servo object
Servo myServo;

// Define the PWM pin for the servo
const int servoPin = 14;

// Define the open and close positions (in degrees)
const int openPosition = 90; // Adjust as needed
const int closePosition = 0; // Adjust as needed

boolean position = 0;

ControllerStream controller(0);

void setup() {

  controller.init("kyle-hotspot", "", 5000);

  // Attach the servo to the PWM pin
  myServo.attach(servoPin);

  // Initialize the servo to the closed position
  myServo.write(closePosition);

  // Optional: Add a small delay to allow the servo to reach the initial position
  delay(1000);
}

void loop() {
  controller.updateData();
  ControllerData controllerData = controller.getControllerData();
  // Open the servo
  
  if (controllerData.getA()) {
    position = openPosition;
  } else if (controllerData.getB()) {
    position = closePosition;
  }
  
  myServo.write(position);
  delay(100);
>>>>>>> 0c1f0502bf266b33ec2331396dad4248f6ce20e9
}
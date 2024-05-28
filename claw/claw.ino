#include "controller.h"

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
}
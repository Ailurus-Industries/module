#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Servo.h>
const char* ssid = "kyle-hotspot";
const char* password =  "";

Servo servo;

WiFiClient client;

bool isPressed = false;

const int servoPin = 16;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);     //Connect to my WiFi router
  Serial.println("");
  Serial.print("Connecting"); //initiall step just displaying connecting
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) { //the llop wiil execute till wifi is not connected
    delay(500);
    Serial.print(".");
  }

  servo.attach(servoPin);

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);// connected to given ssid
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP

  client.connect("10.42.0.54", 5000);
}

void openClaw() {
  servo.write(0);
}

void closeClaw() {
  servo.write(100);
}


void loop(){
  // Serial.println("Sending request...");
  HTTPClient http;
  http.begin(client, "http://10.42.0.54:5000/status");
  // Serial.println(http.GET());
  http.GET();
  int pressed = http.getString().toInt();
  bool currentPressed = pressed > 0;
  if (currentPressed != isPressed) {
    isPressed = currentPressed;
    Serial.println(isPressed ? "pressed" : "released");
  }

  if (isPressed) {
    openClaw();
  } else {
    closeClaw();
  }

  delay(20);
}
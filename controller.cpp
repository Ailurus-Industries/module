#include "controller.h"
#include <WiFi.h>
#include <WiFiUdp.h>

void ControllerData::print()
{
    Serial.print("Header: ");
    Serial.print(header);
    Serial.print(" Index: ");
    Serial.print(index, DEC);
    Serial.print(" Port: ");
    Serial.print(port);
    Serial.print(" Buttons:");
    Serial.print(buttons, BIN);
    Serial.print(" Triggers: ");
    Serial.print(leftTrigger, DEC);
    Serial.print(", ");
    Serial.print(rightTrigger, DEC);
    Serial.print( "Joysticks: ");
    Serial.print(leftX);
    Serial.print(", ");
    Serial.print(leftY);
    Serial.print(", ");
    Serial.print(rightX);
    Serial.print(", ");
    Serial.println(rightY);
}

boolean ControllerData::getDPadUp() 
{
    return (buttons & 0x0001);
}

boolean ControllerData::getDPadDown()
{
    return (buttons & 0x0002) >> 1;
}

boolean ControllerData::getDPadLeft()
{
    return (buttons & 0x0004) >> 2;
}

boolean ControllerData::getDPadRight()
{
    return (buttons & 0x0008) >> 3;
}

boolean ControllerData::getStart()
{
    return (buttons & 0x0010) >> 4;
}

boolean ControllerData::getBack()
{
    return (buttons & 0x0020) >> 5;
}

boolean ControllerData::getLeftThumb()
{
    return (buttons & 0x0040) >> 6;
}

boolean ControllerData::getRightThumb()
{
    return (buttons & 0x0080) >> 7;
}

boolean ControllerData::getLeftShoulder()
{
    return (buttons & 0x0100) >> 8;
}

boolean ControllerData::getRightShoulder()
{
    return (buttons & 0x0200) >> 9;
}

boolean ControllerData::getA()
{
    return (buttons & 0x1000) >> 12;
}

boolean ControllerData::getB()
{
    return (buttons & 0x2000) >> 13;
}

boolean ControllerData::getX()
{
    return (buttons & 0x4000) >> 14;
}

boolean ControllerData::getY()
{
    return (buttons & 0x8000) >> 15;
}

boolean ControllerData::getLeftTriggerPressed()
{
    return leftTrigger > TRIGGER_DEADBAND;
}

boolean ControllerData::getRightTriggerPressed()
{
    return rightTrigger > TRIGGER_DEADBAND;
}

// https://docs.arduino.cc/retired/library-examples/wifi-library/WiFiUdpSendReceiveString/
ControllerStream::ControllerStream(int controllerPort) : controllerPort(controllerPort)
{

}

void ControllerStream::init(char ssid[], char pwd[], int udpPort) 
{
    // Initialize wifi connection
    int status = WiFi.begin(ssid);
    while (status != WL_CONNECTED)
    {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        status = WiFi.begin(ssid);
        // wait 2 seconds for connection:
        delay(2000);
    }

    Serial.println("Connected to WiFi.");
    printWiFiStatus();

    udp.begin(udpPort);
}

void ControllerStream::updateData()
{
    int packetSize = udp.parsePacket();
    if (packetSize < sizeof(ControllerData)) { return; }

    // Read the data
    char data[sizeof(ControllerData)];
    udp.read(data, sizeof(ControllerData));

    // Copy the data into a Controller Data struct
    memcpy(data, &incomingData, sizeof(ControllerData));

    // Verify that packet is valid
    if (incomingData.header[0] != 'C' 
        || incomingData.header[1] != 'O' 
        || incomingData.header[2] != 'N'
        || incomingData.port != controllerPort
    ) 
    {
        Serial.println("Invalid packet recieved!");
        return;
    }

    // Check that packet is new 
    if (incomingData.index > lastMessageIndex) 
    {
        lastMessageIndex = incomingData.index;
        currentData = incomingData;
    }
}

void ControllerStream::printWiFiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your local IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

ControllerData ControllerStream::getControllerData()
{
    return this->currentData;
}
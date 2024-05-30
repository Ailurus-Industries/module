#ifndef CONTROLLER_H
#define CONTROLLER_H

// #include <ESP8266WiFi.h>
#include <WiFi.h>
#include <WiFiUdp.h>

const int TRIGGER_DEADBAND = 50;

typedef struct ControllerData {
    char header[3];
    uint32_t index;
    uint8_t port;
    uint16_t buttons;
    uint8_t leftTrigger;
    uint8_t rightTrigger;
    int16_t leftX;
    int16_t leftY;
    int16_t rightX;
    int16_t rightY;
    void print();
    boolean getDPadUp();
    boolean getDPadDown();
    boolean getDPadLeft();
    boolean getDPadRight();
    boolean getStart();
    boolean getBack();
    boolean getLeftThumb();
    boolean getRightThumb();
    boolean getLeftShoulder();
    boolean getRightShoulder();
    boolean getA();
    boolean getB();
    boolean getX();
    boolean getY();
    boolean getLeftTriggerPressed();
    boolean getRightTriggerPressed();
} __attribute__((packed));

const char HEADER[3] = {'C', 'O', 'N'};

class ControllerStream
{
    private:
        char rawIncomingData[sizeof(ControllerData)];
        int lastMessageIndex = 0;
        int controllerPort;
        ControllerData currentData;
        ControllerData incomingData;
        WiFiUDP udp;
    public:
        ControllerStream(int controllerPort);
        void init(char ssid[], char pwd[], int udpPort);
        void init(char ssid[], int udpPort);
        void updateData();
        void printWiFiStatus();
        ControllerData getControllerData();
};


#endif
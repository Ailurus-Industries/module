#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <WiFi.h>

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
} __attribute__((packed));

const char HEADER[3] = {'C', 'O', 'N'};

class ControllerStream
{
    private:
        int lastMessageIndex = 0;
        int port;
        ControllerData currentData;
    public:
        ControllerStream(int port, char ssid[], char pwd[]);
        ControllerStream(int port, char ssid[]);
};


#endif
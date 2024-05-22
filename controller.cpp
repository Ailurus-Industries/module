#include "controller.h"
#include <WiFi.h>

ControllerStream::ControllerStream(int port, char ssid[], char pwd[]) : port(port)
{
    WiFi.begin(ssid, pwd);
}

ControllerStream::ControllerStream(int port, char ssid[]) : port(port)
{
    WiFi.begin(ssid);
}

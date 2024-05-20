#include "TB6612FNG.h"
#include <ESP32Encoder.h>
#include <FastPID.h>

#ifndef MMGEARMOTOR_H
#define MMGEARMOTOR_H

enum ControlMode { DUTY_CYCLE, POSITION, VELOCITY, NONE };

struct PIDConstants {
    int kP; int kI; int kD;
};

class MMGearMotor
{
private:
    FastPID posPID;
    FastPID velPID;
    TB6612FNG& driver;
    ESP32Encoder encoder;
    int motorID;
    ControlMode currentMode = NONE;
    float setpoint;
    float maxSpeed;
public:
    MMGearMotor(TB6612FNG& motorDriver, int id, int enc1, int enc2, const PIDConstants posConst, const PIDConstants velConst) : driver(motorDriver), motorID(id) {};
    void setControlMode(ControlMode mode);
    void setTargetPosition();
    void setTargetVelocity();
    void setOutput();
    void periodic();
    void stop();
    void zero();
    void setPosition(int pos);
    int getPosition();
};

#endif
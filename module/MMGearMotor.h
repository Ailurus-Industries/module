#ifndef MMGEARMOTOR_H
#define MMGEARMOTOR_H

#include "TB6612FNG.h"
#include <ESP32Encoder.h>
#include <FastPID.h>

enum ControlMode { DUTY_CYCLE, POSITION, VELOCITY, STOP };

struct PIDConstants {
    float kP; float kI; float kD;
};

class MMGearMotor
{
private:
    FastPID posPID;
    FastPID velPID;
    TB6612FNG& driver;
    ESP32Encoder encoder;
    int motorID;
    ControlMode currentMode = STOP;
    int posSetpoint;
    int velSetpoint;
    int maxOutput;
    int lastPos;
    int currPos;
    int velocity;
    int currOutput;
    bool encoderInverted;
    bool outputInverted;
public:
    MMGearMotor(TB6612FNG& motorDriver, int id, int enc1, int enc2, int maxOutput, const PIDConstants posConst, const PIDConstants velConst, bool encoderInverted, bool motorInverted);
    void setControlMode(ControlMode mode);
    void setTargetPosition(int pos);
    void setTargetVelocity(int pos);
    void setOutput(int speed);
    void periodic();
    void stop();
    void zero();
    void setPosition(int pos);
    int getTargetPosition();
    int getPosition();
    int getOutput();
    TB6612FNG& getDriver();
};

#endif
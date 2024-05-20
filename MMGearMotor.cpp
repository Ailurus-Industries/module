#include "MMGearMotor.h"
#include <FastPID.h>
#include <Arduino.h>

MMGearMotor::MMGearMotor(TB6612FNG &motorDriver, int id, int enc1, int enc2, 
                        int maxOutput, PIDConstants posConst, PIDConstants velConst) 
                        : driver(motorDriver), motorID(id), maxOutput(maxOutput)
{
    this->encoder.attachFullQuad(enc1, enc2);
    this->encoder.setCount(0);
    posPID.configure(posConst.kP, posConst.kI, posConst.kD, 10, 16, true);
    velPID.configure(velConst.kP, velConst.kI, velConst.kD, 10, 16, true);
};

void MMGearMotor::periodic()
{   
    currPos = getPosition();
    velocity = currPos - lastPos;
    switch (currentMode) 
    {
        case NONE:
            stop();
            break;
        case DUTY_CYCLE:
            break;
        case POSITION:
            int output = posPID.step(posSetpoint, currPos);
            setOutput(output);
            break;
        case VELOCITY:
            int output = velPID.step(velSetpoint, velocity);
            setOutput(output);
            break;
        default: 
            stop();
            return;
    };
    lastPos = getPosition();
}

void MMGearMotor::stop()
{
    driver.run(motorID, 0);
}

void MMGearMotor::setControlMode(ControlMode mode)
{
    currentMode = currentMode;
}

void MMGearMotor::setTargetPosition(int pos)
{
    posSetpoint = pos;
}

void MMGearMotor::setTargetVelocity(int pos)
{
    velSetpoint = pos;
}

void MMGearMotor::setOutput(int speed)
{
    driver.run(motorID, constrain(speed, -maxOutput, maxOutput));
}

void MMGearMotor::zero()
{
    encoder.setCount(0);
}

void MMGearMotor::setPosition(int pos)
{
    encoder.setCount(pos);
    lastPos = pos;
    currPos = pos;
}

int MMGearMotor::getPosition()
{
    return encoder.getCount();
}

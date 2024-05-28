#include "MMGearMotor.h"
#include <FastPID.h>
#include <Arduino.h>
#include "TB6612FNG.h"

MMGearMotor::MMGearMotor(TB6612FNG &motorDriver, int id, int enc1, int enc2, 
                        int maxOutput, PIDConstants posConst, PIDConstants velConst, bool encoderInverted, bool outputInverted) 
                        : driver(motorDriver), motorID(id), maxOutput(maxOutput), encoderInverted(encoderInverted), outputInverted(outputInverted)
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
        case STOP:
            stop();
            break;
        case DUTY_CYCLE:
            break;
        case POSITION:
            setOutput(posPID.step(posSetpoint, currPos));
            break;
        case VELOCITY:
            setOutput(velPID.step(velSetpoint, velocity));
            break;
    };
    if (-5 <currOutput && 5 > currOutput) { currOutput = 0; }
    driver.run(motorID, outputInverted ? -currOutput : currOutput);
    lastPos = getPosition();
}

void MMGearMotor::stop()
{
    // NOTE: This may cause bugs if speed is set without changing mode
    currOutput = 0;
    currentMode = STOP;
    driver.run(motorID, 0);
}

void MMGearMotor::setControlMode(ControlMode mode)
{
    currentMode = mode;
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
    currOutput = constrain(speed, -maxOutput, maxOutput);
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
    if (encoderInverted) {
        return -encoder.getCount();
    }
    return encoder.getCount();
}

int MMGearMotor::getOutput()
{
    return currOutput;
}

int MMGearMotor::getTargetPosition()
{
    return posSetpoint;
}

TB6612FNG& MMGearMotor::getDriver()
{
    return driver;
}

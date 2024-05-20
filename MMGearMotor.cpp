#include "MMGearMotor.h"
#include <FastPID.h>

MMGearMotor::MMGearMotor(TB6612FNG &motorDriver, int id, int enc1, int enc2, PIDConstants posConst, PIDConstants velConst) : driver(motorDriver), motorID(id) {
    this->encoder.attachFullQuad(enc1, enc2);
    this->encoder.setCount(0);
    posPID.configure(posConst.kP, posConst.kI, posConst.kD, 10, 16, true);
    velPID.configure(velConst.kP, velConst.kI, velConst.kD, 10, 16, true);
};

void MMGearMotor::periodic()
{
    switch (this->currentMode) 
    {
        case NONE:
            stop();
            break;
        case DUTY_CYCLE:
            break;
        case POSITION:
            break;
        case VELOCITY:
            break;
        default: 
            return;
    };
}

void MMGearMotor::stop()
{
    this->driver.run(this->motorID, 0);
}

void MMGearMotor::setControlMode(ControlMode mode)
{
    this->currentMode = currentMode;
}

void MMGearMotor::setTargetPosition()
{
    
}

void MMGearMotor::setTargetVelocity()
{
}

void MMGearMotor::setOutput()
{
}

void MMGearMotor::zero()
{
    this->encoder.setCount(0);
}

void MMGearMotor::setPosition(int pos)
{
    this->encoder.setCount(pos);
}

int MMGearMotor::getPosition()
{
    return this->encoder.getCount();
}

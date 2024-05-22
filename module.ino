#include "MMGearMotor.h"
#include "controller.h"

// 39 DIN2     
// 36 DIN1     
// 35 CIN2     
// 34 CIN1     
// 33 BIN2     
// 32 BIN1     
// 27 AIN2     
// 26 AIN1     
// 25 PWMB     23 PWMD 
// 19 BOUT2    22 DOUT2
// 18 BOUT1    21 DOUT1
// 15 PWMA     17 PWMC 
// 14 AOUT2    16 COUT2
// 13 AOUT1    5  COUT1
// 12 STBY1    4  STBY2


// Motor Controller #1
#define PWMA  15
#define AOUT1 14
#define AOUT2 13
#define PWMB  25
#define BOUT1 18
#define BOUT2 19
#define STBY1 12

// Encoder Pins
#define AIN1 26
#define AIN2 27
#define BIN1 32
#define BIN2 33

// Motor Controller #2
#define PWMC  17
#define COUT1 5
#define COUT2 16
#define PWMD  23
#define DOUT1 21
#define DOUT2 22
#define STBY2 4

// Encoder Pins
#define CIN1 34
#define CIN2 35
#define DIN1 36
#define DIN2 39


// Out of 255: 6V out of 8.4 V = 182
#define MAX_SPEED 180

const PIDConstants positionPID = {0.5, 0, 0.0005};
const PIDConstants velocityPID = {0, 0, 0};

const int gearRatio = 298 * 12;

TB6612FNG driverAB(PWMA, PWMB, AOUT1, AOUT2, BOUT1, BOUT2, STBY1);
TB6612FNG driverCD(PWMC, PWMD, COUT1, COUT2, DOUT1, DOUT2, STBY2);

// drive motors
MMGearMotor a(driverAB, 0, AIN1, AIN2, MAX_SPEED, positionPID, velocityPID, true);
MMGearMotor b(driverAB, 1, BIN1, BIN2, MAX_SPEED, positionPID, velocityPID, true);

// face motors 
MMGearMotor c(driverCD, 0, CIN1, CIN2, MAX_SPEED, positionPID, velocityPID, true);
MMGearMotor d(driverCD, 1, DIN1, DIN2, MAX_SPEED, positionPID, velocityPID, true);

ControllerStream controller(0);

int faceMotorRightPosition = 0;
int faceMotorLeftPosition = 0;

const int deltaFaceMotorPosition = 1;

void setup()
{
    Serial.begin(115200);
    controller.init("kyle-hotspot", "", 5000);
    
    // Stop all motors
    a.setControlMode(DUTY_CYCLE);
    a.setOutput(0);
    b.setControlMode(DUTY_CYCLE);
    b.setOutput(0);
    c.setControlMode(DUTY_CYCLE);
    c.setOutput(0);
    d.setControlMode(DUTY_CYCLE);
    d.setOutput(0);

    delay(2000);
}

void loop()
{
    controller.updateData();
    ControllerData controllerData = controller.getControllerData();
    controllerData.print();

    /*
    if (controller.getControllerData().getLeftTriggerPressed()) {
        a.setControlMode(DUTY_CYCLE);
        a.setOutput(map(controller.getControllerData().leftY, 0, 32767, 0, 100));
    } else if (controller.getControllerData().getRightTriggerPressed()) {
        float angle = atan2(controller.getControllerData().leftY, controller.getControllerData().leftX);
        
        int targetTicks = (int) ((angle / (2*PI)) * 12 * 298);
        Serial.print("Target ticks: ");
        Serial.println(targetTicks);
        a.setControlMode(POSITION);
        a.setTargetPosition(targetTicks);
    } else {
        a.stop();
    }
    */

    if (controllerData.getLeftTriggerPressed() && controllerData.getRightTriggerPressed())
    {
        // drive
        a.setControlMode(DUTY_CYCLE);
        a.setOutput(map(controllerData.leftY, 0, 32767, 0, 100));
        b.setControlMode(DUTY_CYCLE);
        b.setOutput(map(controllerData.rightY, 0, 32767, 0, 100));

        if (controllerData.getDPadUp() == true)
        {
            faceMotorRightPosition += deltaFaceMotorPosition;
            faceMotorLeftPosition += deltaFaceMotorPosition;
        }

        if (controllerData.getDPadDown() == true)
        {
            faceMotorRightPosition -= deltaFaceMotorPosition;
            faceMotorLeftPosition -= deltaFaceMotorPosition;
        }

        if (controllerData.getDPadRight() == true)
        {
            faceMotorRightPosition += deltaFaceMotorPosition;
            faceMotorLeftPosition -= deltaFaceMotorPosition;
        }

        if (controllerData.getDPadLeft() == true)
        {
            faceMotorRightPosition -= deltaFaceMotorPosition;
            faceMotorLeftPosition += deltaFaceMotorPosition;
        }

        // face
        c.setControlMode(POSITION);
        c.setTargetPosition(faceMotorRightPosition);
        d.setControlMode(POSITION);
        d.setTargetPosition(faceMotorLeftPosition);
    }
    else
    {
        // Stop all motors if button is not held
        a.stop();
        b.stop();
        c.stop();
        d.stop();
    }

    if (controllerData.getStart()) 
    {
        a.zero();
        b.zero();
        c.zero();
        d.zero();
    }
    
    a.periodic();
    b.periodic();
    c.periodic();
    d.periodic();
    printMotorPositions();

    delay(100);
}

void printMotorPositions() 
{
    Serial.print("posA:");
    Serial.print(a.getPosition());
    Serial.print(",outputA:");
    Serial.print(a.getOutput());
    Serial.print("posB:");
    Serial.print(b.getPosition());
    Serial.print(",outputB:");
    Serial.print(b.getOutput());
    Serial.print("posC:");
    Serial.print(c.getPosition());
    Serial.print(",outputC:");
    Serial.print(c.getOutput());
    Serial.print("posD:");
    Serial.print(d.getPosition());
    Serial.print(",outputD:");
    Serial.println(d.getOutput());
}

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
// 15 STBY1    17 STBY2
// 14 AOUT1    16 COUT1
// 13 AOUT2     5 COUT2
// 12 PWMA      4 PWMC


// Motor Controller #1
#define PWMA  12
#define AOUT1 14
#define AOUT2 13
#define PWMB  25
#define BOUT1 18
#define BOUT2 19
#define STBY1 15

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

const PIDConstants positionPID = {0.5, 0, 0.01};
const PIDConstants velocityPID = {0, 0, 0};

const int gearRatio = 298 * 12;

TB6612FNG driverAB(PWMA, PWMB, AOUT1, AOUT2, BOUT1, BOUT2, STBY1);
TB6612FNG driverCD(PWMC, PWMD, COUT1, COUT2, DOUT1, DOUT2, STBY2);

// face motors
MMGearMotor a(driverAB, 0, AIN1, AIN2, MAX_SPEED, positionPID, velocityPID, false, false);
MMGearMotor b(driverAB, 1, BIN1, BIN2, MAX_SPEED, positionPID, velocityPID, false, false);

// drive motors 
MMGearMotor c(driverCD, 0, CIN1, CIN2, MAX_SPEED, positionPID, velocityPID, true, false);
MMGearMotor d(driverCD, 1, DIN1, DIN2, MAX_SPEED, positionPID, velocityPID, false, false);

ControllerStream controller(0);

int faceMotorRightPosition = 0;
int faceMotorLeftPosition = 0;

const int translationStep = 50;
const int rotationStep = 500;

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

int lastRightPos = 0;
int lastLeftPos = 0;
int topFacePos = 0;
int topFaceRot = 0;
// const int maxTopFacePos = 1000;
// const int minTopFacePos = -1000;

void loop()
{
    controller.updateData();
    ControllerData controllerData = controller.getControllerData();
    // controllerData.print();

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
    
    int newRightPos = a.getPosition();
    int newLeftPos = b.getPosition();
    int rightDiff = newRightPos - lastRightPos;
    int leftDiff = newLeftPos - lastLeftPos;
    // Note: should be the other way around, but one of the faces is inverted
    topFacePos += (rightDiff - leftDiff) / 2;
    topFaceRot += (rightDiff + leftDiff) / 2;
    lastRightPos = newRightPos;
    lastLeftPos = newLeftPos;

    Serial.print("Top pos:");
    Serial.print(topFacePos);
    Serial.print(",Top rot:");
    Serial.println(topFaceRot);

    if (controllerData.getLeftTriggerPressed() && controllerData.getRightTriggerPressed())
    {
        // drive
        c.setControlMode(DUTY_CYCLE);
        c.setOutput(map(controllerData.leftY, 0, 32767, 0, 100));
        d.setControlMode(DUTY_CYCLE);
        d.setOutput(map(controllerData.rightY, 0, 32767, 0, 100));

        if (controllerData.getDPadUp() == true)
        {
            faceMotorRightPosition -= translationStep;
            faceMotorLeftPosition += translationStep;
        }

        if (controllerData.getDPadDown() == true)
        {
            faceMotorRightPosition += translationStep;
            faceMotorLeftPosition -= translationStep;
        }

        if (controllerData.getDPadRight() == true)
        {
            faceMotorRightPosition -= rotationStep;
            faceMotorLeftPosition -= rotationStep;
        }

        if (controllerData.getDPadLeft() == true)
        {
            faceMotorRightPosition += rotationStep;
            faceMotorLeftPosition += rotationStep;
        }

        // face
        a.setControlMode(POSITION);
        a.setTargetPosition(faceMotorRightPosition);
        b.setControlMode(POSITION);
        b.setTargetPosition(faceMotorLeftPosition);
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
        lastRightPos = 0;
        lastLeftPos = 0;
        topFacePos = 0;
        topFaceRot = 0;
        faceMotorLeftPosition = 0;
        faceMotorRightPosition = 0;
    }

    if (controllerData.getBack() || controllerData.getStart())
    {
        a.setTargetPosition(0);
        b.setTargetPosition(0);
        c.setTargetPosition(0);
        d.setTargetPosition(0);
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
    Serial.print(",targetPosA:");
    Serial.print(a.getTargetPosition());
    Serial.print(",outputA:");
    Serial.print(a.getOutput());
    Serial.print(",posB:");
    Serial.print(b.getPosition());
    Serial.print(",outputB:");
    Serial.print(b.getOutput());
    Serial.print(",targetPosB:");
    Serial.print(b.getTargetPosition());
    Serial.print(",posC:");
    Serial.print(c.getPosition());
    Serial.print(",outputC:");
    Serial.print(c.getOutput());
    // Serial.print("targetPosC:");
    // Serial.print(c.getTargetPosition());
    Serial.print(",posD:");
    Serial.print(d.getPosition());
    Serial.print(",outputD:");
    Serial.println(d.getOutput());
    // Serial.print("targetPosD:");
    // Serial.print(d.getTargetPosition());
}

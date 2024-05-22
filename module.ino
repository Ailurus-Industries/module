// #include "MMGearMotor.h"

// // 39 DIN2     
// // 36 DIN1     
// // 35 CIN2     
// // 34 CIN1     
// // 33 BIN2     
// // 32 BIN1     
// // 27 AIN2     
// // 26 AIN1     
// // 25 PWMB     23 PWMD 
// // 19 BOUT2    22 DOUT2
// // 18 BOUT1    21 DOUT1
// // 15 PWMA     17 PWMC 
// // 14 AOUT2    16 COUT2
// // 13 AOUT1    5  COUT1
// // 12 STBY1    4  STBY2


// // Motor Controller #1
// #define PWMA  15
// #define AOUT1 14
// #define AOUT2 13
// #define PWMB  25
// #define BOUT1 18
// #define BOUT2 19
// #define STBY1 12

// // Encoder Pins
// #define AIN1 26
// #define AIN2 27
// #define BIN1 32
// #define BIN2 33

// // Motor Controller #2
// #define PWMC  17
// #define COUT1 5
// #define COUT2 16
// #define PWMD  23
// #define DOUT1 21
// #define DOUT2 22
// #define STBY2 4

// // Encoder Pins
// #define CIN1 34
// #define CIN2 35
// #define DIN1 36
// #define DIN2 39


// // Out of 255: 6V out of 8.4 V = 182
// #define MAX_SPEED 180

// const PIDConstants positionPID = {0.1, 0, 0};
// const PIDConstants velocityPID = {0, 0, 0};

// TB6612FNG driverAB(PWMA, PWMB, AOUT1, AOUT2, BOUT1, BOUT2, STBY1);
// TB6612FNG driverCD(PWMC, PWMD, COUT1, COUT2, DOUT1, DOUT2, STBY2);

// MMGearMotor a(driverAB, 0, AIN1, AIN2, MAX_SPEED, positionPID, velocityPID);
// // MMGearMotor b(driverAB, 1, BIN1, BIN2, MAX_SPEED, positionPID, velocityPID);
// // MMGearMotor c(driverCD, 0, CIN1, CIN2, MAX_SPEED, positionPID, velocityPID);
// // MMGearMotor d(driverCD, 1, DIN1, DIN2, MAX_SPEED, positionPID, velocityPID);

void setup()
{
//     Serial.begin(115200);
//     a.setControlMode(DUTY_CYCLE);
//     a.setOutput(50);
}

void loop()
{
// 	a.periodic();
//     Serial.print("Pos: ");
//     Serial.print(a.getPosition());
//     Serial.print(" Output: ");
//     Serial.println(a.getOutput());
//     delay(100);
}

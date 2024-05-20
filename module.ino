#include "MMGearMotor.h"

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

const PIDConstants positionPID = {1, 0, 0};
TB6612FNG motorDriver(PWMA, PWMB, AOUT1, AOUT2, BOUT1, BOUT2, STBY1);

MMGearMotor a(motorDriver, 0, AIN1, AIN2, positionPID, positionPID);

void setup()
{
    
}

void loop()
{
	
}

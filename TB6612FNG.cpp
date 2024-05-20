#include "TB6612FNG.h"
#include <Arduino.h>

TB6612FNG::TB6612FNG(int PWMA, int PWMB, int AIN1, int AIN2, int BIN1, int BIN2, int STBY) {
    this->STBY = STBY;
    this->PWMA = PWMA;
    this->PWMB = PWMA;
    this->AIN1 = AIN1;
    this->AIN2 = AIN2;
    this->BIN1 = BIN1;
    this->BIN2 = BIN2;

    pinMode(STBY, OUTPUT);

    pinMode(PWMA, OUTPUT);
    pinMode(PWMB, OUTPUT);

    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
}

/**
 * @brief Sets the speed of the specified motor.
 * 
 * @param motor 0 for A, 1 for B
 * @param speed integer ranging from -255 to 255.
 */
void TB6612FNG::run(int motor, int speed) {
    digitalWrite(STBY, HIGH); //disable standby

    // set direction based on speed 
    boolean inPin1;
    boolean inPin2;
    if (speed > 0) {
        inPin1 = HIGH;
        inPin2 = LOW;
    } else if (speed < 0) {
        inPin1 = LOW;
        inPin2 = HIGH;
    } else {
        inPin1 = LOW;
        inPin2 = LOW;
    }

    // set speed based on motor
    if(motor == 0){
        digitalWrite(AIN1, inPin1);
        digitalWrite(AIN2, inPin2);
        analogWrite(PWMA, speed);
    } else if (motor == 1) {
        digitalWrite(BIN1, inPin1);
        digitalWrite(BIN2, inPin2);
        analogWrite(PWMB, speed);
    }
}

void TB6612FNG::stop(int motor) {
    if (motor == 1) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);    
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    } else if (motor == 2) {
        digitalWrite(AIN1, LOW);
        digitalWrite(AIN2, LOW);
        digitalWrite(BIN1, LOW);
        digitalWrite(BIN2, LOW);
    }
}


// stop both motors connected to controller
void TB6612FNG::standby(){
    digitalWrite(STBY, LOW);
    analogWrite(PWMA, 0);
    analogWrite(PWMB, 0);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
}
#include <Arduino.h>

const int MotorA1 = 6;  //in3
const int MotorA2 = 7; //in4

const int MotorB1 = 4; // in 2
const int MotorB2 = 5; // in 1

void moveSetup(){
    pinMode(MotorA1, OUTPUT);
    pinMode(MotorA2, OUTPUT);
    pinMode(MotorB1, OUTPUT);
    pinMode(MotorB2, OUTPUT);

    // moveStop();
}

void moveForward() {
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);

    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
}

void moveStop(){
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);

    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);  
}

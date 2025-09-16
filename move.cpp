#include <Arduino.h>

const int MotorB1 = 4; // in1
const int MotorB2 = 5; // in2

const int MotorA2 = 6;  //in3
const int MotorA1 = 7; // in4

void moveSetup(){
    pinMode(MotorA1, OUTPUT);
    pinMode(MotorA2, OUTPUT);
    pinMode(MotorB1, OUTPUT);
    pinMode(MotorB2, OUTPUT);
}

void moveBackward() {
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);

    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
}

void moveForward() {
    digitalWrite(MotorA1, HIGH);
    digitalWrite(MotorA2, LOW);

    digitalWrite(MotorB1, HIGH);
    digitalWrite(MotorB2, LOW);
}

void moveForwardLeft(){
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);

    digitalWrite(MotorB1, HIGH);
    digitalWrite(MotorB2, LOW);
}

void moveForwardRight(){
    digitalWrite(MotorA1, HIGH);
    digitalWrite(MotorA2, LOW);

    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);
}

// void moveBackwardRight(){
//     digitalWrite(MotorA1, LOW);
//     digitalWrite(MotorA2, LOW);

//     digitalWrite(MotorB1, LOW);
//     digitalWrite(MotorB2, HIGH);
// }

// void moveBackwardLeft(){
//     digitalWrite(MotorA1, LOW);
//     digitalWrite(MotorA2, HIGH);

//     digitalWrite(MotorB1, LOW);
//     digitalWrite(MotorB2, LOW);
// }

void moveStop(){
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);

    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);  
}

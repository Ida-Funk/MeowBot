#include <Arduino.h>
#include "move.h"

// Motorpinnar – justera efter hårdvara
const int IN1 = 5;
const int IN2 = 4;
const int IN3 = 6;
const int IN4 = 7;

// const int MotorB1 = 4; // in1
// const int MotorB2 = 5; // in2

// const int MotorA2 = 6;  //in3
// const int MotorA1 = 7; // in4

void moveSetup(){
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
}

// void moveBackward() {
//     digitalWrite(MotorA1, LOW);
//     digitalWrite(MotorA2, HIGH);

//     digitalWrite(MotorB1, LOW);
//     digitalWrite(MotorB2, HIGH);
// }

// void moveForward() {
//     digitalWrite(MotorA1, HIGH);
//     digitalWrite(MotorA2, LOW);

//     digitalWrite(MotorB1, HIGH);
//     digitalWrite(MotorB2, LOW);
// }

// void moveForwardLeft(){
//     digitalWrite(MotorA1, LOW);
//     digitalWrite(MotorA2, LOW);

//     digitalWrite(MotorB1, HIGH);
//     digitalWrite(MotorB2, LOW);
// }

// void moveForwardRight(){
//     digitalWrite(MotorA1, HIGH);
//     digitalWrite(MotorA2, LOW);

//     digitalWrite(MotorB1, LOW);
//     digitalWrite(MotorB2, LOW);
// }

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
    digitalWrite(IN1, 0); 
    digitalWrite(IN2, 0);

    digitalWrite(IN3, 0); 
    digitalWrite(IN4, 0);  
}
void moveBackward(int spd) {
  digitalWrite(IN1, spd); digitalWrite(IN2, 0);
  digitalWrite(IN3, spd); digitalWrite(IN4, 0);
}
void moveForward(int spd) {
  digitalWrite(IN1, 0);   digitalWrite(IN2, spd);
  digitalWrite(IN3, 0);   digitalWrite(IN4, spd);
}
void moveRight(int spd) {
  digitalWrite(IN1, 0);   digitalWrite(IN2, spd);
  digitalWrite(IN3, spd); digitalWrite(IN4, 0);
}
void moveLeft(int spd) {
  digitalWrite(IN1, spd); digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);   digitalWrite(IN4, spd);
}


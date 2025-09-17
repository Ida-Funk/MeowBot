#include <Arduino.h>
#include "move.h"

// Motorpinnar – justera efter hårdvara
const int IN1 = 5;
const int IN2 = 4;
const int IN3 = 6;
const int IN4 = 7;

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
void moveForward(int spd) {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}
void moveBackward(int spd) {
  digitalWrite(IN1, 0);   digitalWrite(IN2, spd);
  digitalWrite(IN3, 0);   digitalWrite(IN4, spd);
}
void moveLeft(int spd) {
  digitalWrite(IN1, 0);   digitalWrite(IN2, spd);
  digitalWrite(IN3, spd); digitalWrite(IN4, 0);
}
void moveRight(int spd) {
  digitalWrite(IN1, spd); digitalWrite(IN2, 0);
  digitalWrite(IN3, 0);   digitalWrite(IN4, spd);
}


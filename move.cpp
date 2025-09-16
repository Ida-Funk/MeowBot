#include <Arduino.h>

const int LEFT_FORWARD_PIN = 1;
const int LEFT_BACKWARD_PIN = 2;
const int RIGHT_FORWARD_PIN = 3;
const int RIGHT_BACKWARD_PIN = 4;

void setup() {
    pinMode(LEFT_FORWARD, OUTPUT);
    pinMode(LEFT_BACKWARD, OUTPUT);
    pinMode(RIGHT_FORWARD, OUTPUT);
    pinMode(RIGHT_BACKWARD, OUTPUT);
}

void moveForward() {
    digitalWrite(LEFT_FORWARD, HIGH);
    digitalWrite(LEFT_BACKWARD, LOW);
    digitalWrite(RIGHT_FORWARD, HIGH);
    digitalWrite(RIGHT_BACKWARD, LOW);
}

void moveBackward() {
    digitalWrite(LEFT_FORWARD, LOW);
    digitalWrite(LEFT_BACKWARD, HIGH);
    digitalWrite(RIGHT_FORWARD, LOW);
    digitalWrite(RIGHT_BACKWARD, HIGH);
}

void turnRight() {
    digitalWrite(LEFT_FORWARD, HIGH);
    digitalWrite(LEFT_BACKWARD, LOW);
    digitalWrite(RIGHT_FORWARD, LOW);
    digitalWrite(RIGHT_BACKWARD, HIGH);
}

void turnLeft() {
    digitalWrite(LEFT_FORWARD, LOW);
    digitalWrite(LEFT_BACKWARD, HIGH);
    digitalWrite(RIGHT_FORWARD, HIGH);
    digitalWrite(RIGHT_BACKWARD, LOW);
}

void stopMotors() {
    digitalWrite(LEFT_FORWARD, LOW);
    digitalWrite(LEFT_BACKWARD, LOW);
    digitalWrite(RIGHT_FORWARD, LOW);
    digitalWrite(RIGHT_BACKWARD, LOW);
}
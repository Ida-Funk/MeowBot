#pragma once
#include <Arduino.h>
#ifndef MOVE_H
#define MOVE_H

// extern const int motorLeft;
// extern const int motorRight;
void moveSetup();  // init pins, stoppa motorer

void moveForward(int spd);
void moveBackward(int spd);
void moveLeft(int spd);
void moveRight(int spd);

// void moveForward();
// void moveForwardLeft();
// void moveForwardRight();
// void moveBackward();

void moveStop();

#endif

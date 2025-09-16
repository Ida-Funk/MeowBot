#pragma once
#include <Arduino.h>

void moveSetup();  // init pins, stoppa motorer

void moveForward(int spd);
void moveBackward(int spd);
void moveLeft(int spd);
void moveRight(int spd);
void moveStop();

#include <Arduino.h>
#include "app.h"
#include "move.h"
#include "sound.h"

//extern IRrecv IrReceiver;

// Ultraljudspinnar
const int TRIG_PIN = A4;
const int ECHO_PIN = A5;

void appSetup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

long distanceCM() {
  digitalWrite(TRIG_PIN, LOW); delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  unsigned long dur = pulseIn(ECHO_PIN, HIGH, 25000UL);
  return (dur == 0) ? 500 : (dur * 0.0343 / 2.0);
}

void hopAndPlaySafe() {
  const int STOP_CM = 18;
  const int WARN_CM = 30;

  // backa lite
  moveBackward(120); delay(220);
  moveStop();

  // hopp framåt – avbryt om hinder
  unsigned long t0 = millis();
  while (millis() - t0 < 300) {
    if (distanceCM() <= STOP_CM) {
      moveStop();
     // IrReceiver.stop();
     // hiss(400);
      //IrReceiver.start();
      moveBackward(160); delay(220);
      moveLeft(170); delay(220);
      moveStop();
      return;
    }
    moveForward(255);
    delay(40);
  }
  moveStop();

  // lek – zig-zag
  moveLeft(180); delay(180);
  moveRight(180); delay(180);
  moveForward(120); delay(220);
  moveStop();

  // ljud
  //IrReceiver.stop();
  //chirp(240);
  //purr(700);
  //IrReceiver.start();
}

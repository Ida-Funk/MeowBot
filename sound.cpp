
// ...existing code...
#include <Arduino.h>
#include "sound.h"
extern volatile int currentCommand;

const int BUZZER_PIN = 8;

void meow() {
    for (int m = 0; m < 4; m++) {
        for (int freq = 1200; freq >= 600; freq -= 5) {
            tone(BUZZER_PIN, freq);
            delay(3);
        }
        noTone(BUZZER_PIN);
        if(m < 3){
            delay (400);
        }
    }
}

void hiss(unsigned long ms) {
    unsigned long t0 = millis();
    while (millis() - t0 < ms) {
        int f = random(3000, 6000);
        tone(BUZZER_PIN, f);
        delay(2);
    }
    noTone(BUZZER_PIN);
}

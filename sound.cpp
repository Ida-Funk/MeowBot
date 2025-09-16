

#include <Arduino.h>
#include "sound.h"
extern volatile int currentCommand;

const int BUZZER_PIN = 8;

void meow() {
    for (int m = 0; m < 4; m++) {
        for (int freq = 1200; freq >= 600; freq -= 2) {
            tone(BUZZER_PIN, freq);
            delay(6);
        }
        noTone(BUZZER_PIN);
        if(m < 3){
            delay (700);
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

void purr(unsigned long ms) {
  unsigned long t0 = millis();
  const int baseHz = 120;

  while (millis() - t0 < ms) {
    int f = baseHz + random(-10, 11);
    int burst = random(10, 21);
    int gap   = random(5, 16);
    tone(BUZZER_PIN, f, burst);
    delay(burst);
    noTone(BUZZER_PIN);
    delay(gap);
  }
}  

// ---------------- chirp ----------------
void chirp(uint16_t durMs) {
  unsigned long t0 = millis();
  for (int f = 1800; f <= 2400; f += 60) {
    tone(BUZZER_PIN, f, 10);
    delay(8);
    if (millis() - t0 > durMs) break;
  }
  for (int f = 2400; f >= 1400; f -= 80) {
    tone(BUZZER_PIN, f, 12);
    delay(9);
    if (millis() - t0 > durMs) break;
  }
  noTone(BUZZER_PIN);
}

// ---------------- chatter ----------------
void chatter(uint16_t reps, uint16_t rateMs) {
  for (uint16_t i = 0; i < reps; i++) {
    int f    = 2100 + (rand() % 1200);
    int onMs = 15 + (rand() % 8);
    int offMs = (int)max(5, (int)rateMs - onMs);
    tone(BUZZER_PIN, f, onMs);
    delay(onMs);
    noTone(BUZZER_PIN);
    delay(offMs);
  }
}

// ---------------- growl ----------------
void growl(uint16_t durMs) {
  unsigned long t0 = millis();
  while (millis() - t0 < durMs) {
    // Växla mellan två riktigt låga toner
    int f1 = 70 + (rand() % 10);  // 70–80 Hz
    int f2 = 90 + (rand() % 15);  // 90–105 Hz

    // Kör korta burst med f1 och f2 omväxlande
    tone(BUZZER_PIN, f1, 40);
    delay(40);
    noTone(BUZZER_PIN);
    delay(10);

    tone(BUZZER_PIN, f2, 50);
    delay(50);
    noTone(BUZZER_PIN);
    delay(15);
  }
}

// --- CATERWAUL ---
// Långt “ylande” jam: glissando upp och ned med lite vibrato.
void caterwaul(uint16_t durMs) {
  unsigned long t0 = millis();

  // Grundram: svep mellan 600–1600 Hz
  const int fLow  = 600;
  const int fHigh = 1600;

  // Vibrato-parametrar (svag, långsam)
  // amplitud ~ +/- 30 Hz, period ~ 60–90 ms
  while (millis() - t0 < durMs) {
    // Upp-svep
    for (int f = fLow; f <= fHigh; f += 20) {
      int vib = (random(0, 2) ? 1 : -1) * random(10, 35); // liten vibrato-variation
      int ff = max(100, f + vib);
      tone(BUZZER_PIN, ff, 15);
      delay(12);
      if (millis() - t0 > durMs) break;
    }
    if (millis() - t0 > durMs) break;

    // Ned-svep (lite långsammare för dramatik)
    for (int f = fHigh; f >= fLow; f -= 15) {
      int vib = (random(0, 2) ? 1 : -1) * random(10, 35);
      int ff = max(100, f + vib);
      tone(BUZZER_PIN, ff, 18);
      delay(14);
      if (millis() - t0 > durMs) break;
    }
  }
  noTone(BUZZER_PIN);
}

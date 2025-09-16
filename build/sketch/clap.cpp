#line 1 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\MeowBot\\clap.cpp"
#include <Arduino.h>
#include "clap.h"

static int MIC_PIN;
static float levelEMA = 512.0;
static float noiseEMA = 0.0;
static unsigned long lastPeakMs = 0;
static unsigned long firstClapMs = 0;
static bool waitingSecond = false;

const float EMA_ALPHA_LEVEL = 0.01;
const float EMA_ALPHA_NOISE = 0.05;
const int CLAP_MARGIN = 80;
const int CLAP_DEBOUNCE_MS = 120;
const int DOUBLE_CLAP_WINDOW_MS = 400;

void clapSetup(int micPin) {
  MIC_PIN = micPin;
  pinMode(MIC_PIN, INPUT);
}

ClapEvent updateClapDetector() {
  int s = analogRead(MIC_PIN);
  levelEMA = (1.0 - EMA_ALPHA_LEVEL) * levelEMA + EMA_ALPHA_LEVEL * s;
  float dev = fabs(s - levelEMA);
  noiseEMA = (1.0 - EMA_ALPHA_NOISE) * noiseEMA + EMA_ALPHA_NOISE * dev;
  float thresh = noiseEMA + CLAP_MARGIN;

  unsigned long now = millis();

  if (dev > thresh) {
    if (now - lastPeakMs > CLAP_DEBOUNCE_MS) {
      lastPeakMs = now;
      if (!waitingSecond) {
        waitingSecond = true;
        firstClapMs = now;
      } else {
        if (now - firstClapMs <= DOUBLE_CLAP_WINDOW_MS) {
          waitingSecond = false;
          return DOUBLE_CLAP;
        } else {
          firstClapMs = now;
        }
      }
    }
  }

  if (waitingSecond && (now - firstClapMs > DOUBLE_CLAP_WINDOW_MS)) {
    waitingSecond = false;
    return SINGLE_CLAP;
  }

  return NONE;
}

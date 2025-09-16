#define RECV_PIN 11
#define BUZZER_PIN 8
#include <IRremote.h>
#include "sound.h"
#include "clap.h"

// --- IR-knappar (raw codes från sniff) ---
#define IR_BTN_1      0xFB040707
#define IR_BTN_2      0xFA050707
#define IR_BTN_3      0xF9060707
#define IR_BTN_4      0xF7080707
#define IR_BTN_5      0xF6090707
#define IR_BTN_6      0xF50A0707
#define IR_BTN_UP     0x9F600707
#define IR_BTN_DOWN   0x9E610707
#define IR_BTN_LEFT   0x9A650707
#define IR_BTN_RIGHT  0x9D620707

IRrecv irrecv(RECV_PIN);

volatile int currentCommand = 0; // 4=meow, 5=hiss (enligt din switch)
const int MIC_PIN = A0;          // ← mic på A0


void setup() {
  Serial.begin(115200);
  Serial.println("Start");
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Starta mottagaren
  clapSetup(MIC_PIN);            // ← starta klappdetektering
}

void loop() {
  // --- IR-mottagning (RAW + filter) ---
  if (IrReceiver.decode()) {
    auto &d = IrReceiver.decodedIRData;

    // hoppa över repeat, okänt protokoll och nollvärden
    if (!(d.flags & IRDATA_FLAGS_IS_REPEAT) &&
        d.protocol != UNKNOWN &&
        d.decodedRawData != 0) {

      uint32_t raw = d.decodedRawData;
      Serial.print("IR raw=0x"); Serial.println(raw, HEX);

      if (raw == IR_BTN_1)         currentCommand = 4;  // meow
      else if (raw == IR_BTN_2)    currentCommand = 5;  // hiss
      else if (raw == IR_BTN_UP)   {/* currentCommand = 10; */}
      else if (raw == IR_BTN_DOWN) {/* currentCommand = 11; */}
      else if (raw == IR_BTN_LEFT) {/* currentCommand = 12; */}
      else if (raw == IR_BTN_RIGHT){/* currentCommand = 13; */}
    }
    IrReceiver.resume();
  }

  ClapEvent ev = updateClapDetector();
  if (ev == SINGLE_CLAP) {
    currentCommand = 4;  // meow
    Serial.println("Clap: SINGLE -> meow");
  } else if (ev == DOUBLE_CLAP) {
    currentCommand = 5;  // hiss
    Serial.println("Clap: DOUBLE -> hiss");
  }

  // --- Kör exakt ETT kommando, stoppa IR under tone() ---
  static unsigned long lastActionMs = 0;        // enkel cooldown
  const unsigned long COOLDOWN_MS = 150;        // fintrimma vid behov

  if (currentCommand != 0 && millis() - lastActionMs > COOLDOWN_MS) {
    lastActionMs = millis();

    switch (currentCommand) {
      case 4:
        Serial.println("meow() start");
        IrReceiver.stop();
        meow();
        IrReceiver.start(); // 
        Serial.println("meow() end");
        break;

      case 5:
        Serial.println("hiss() start");
        IrReceiver.stop();
        hiss(600);
        IrReceiver.start();
        Serial.println("hiss() end");
        break;

      // case 10..13: lägg motor/servo-styrning här om du vill
    }
    currentCommand = 0;  // viktigt: nollställ
  }
}


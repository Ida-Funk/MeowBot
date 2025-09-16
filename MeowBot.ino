#define RECV_PIN 11
#define BUZZER_PIN 8

#include <IRremote.h>
#include "sound.h"
#include "clap.h"
#include "move.h"
#include "app.h"

#define TRIG_PIN A4    // Välj rätt pin-nummer för din hårdvara
#define ECHO_PIN A5   // Välj rätt pin-nummer för din hårdvara
// --- IR-knappar (raw codes från sniff) ---
#define IR_BTN_1      0xFB040707
#define IR_BTN_2      0xFA050707
#define IR_BTN_3      0xF9060707
#define IR_BTN_4      0xF7080707
#define IR_BTN_5      0xF6090707
#define IR_BTN_6      0xF50A0707
#define IR_BTN_7      0xF30C0707
#define IR_BTN_8      0xF20D0707
#define IR_BTN_9      0xF10E0707
#define IR_BTN_UP     0x9F600707
#define IR_BTN_DOWN   0x9E610707
#define IR_BTN_LEFT   0x9A650707
#define IR_BTN_RIGHT  0x9D620707
#define IR_BTN_MID  0x97680707
IRrecv irrecv(RECV_PIN);

volatile int currentCommand = 0; // 4=meow, 5=hiss (enligt din switch)
const int MIC_PIN = A0;          // ← mic på A0

void setup() {  
    moveSetup();

    Serial.begin(115200);
    Serial.println("Start");
    IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Starta mottagaren
    clapSetup(MIC_PIN);            // ← starta klappdetektering
    appSetup();
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
      else if (raw == IR_BTN_3)    currentCommand = 6;  // purr
      else if (raw == IR_BTN_4)    currentCommand = 7;  // chirp
      else if (raw == IR_BTN_5)   currentCommand = 8;  // chatter
      //else if (raw == IR_BTN_6) currentCommand = 9;  // growl
      else if (raw == IR_BTN_6)    currentCommand = 14; 
      else if (raw == IR_BTN_UP)  currentCommand = 10;
      else if (raw == IR_BTN_DOWN) {
        currentCommand = 11;
    }
      else if (raw == IR_BTN_LEFT) {/* currentCommand = 12; */}
      else if (raw == IR_BTN_RIGHT){/* currentCommand = 13; */}
      else if (raw == IR_BTN_MID){ currentCommand = 20; }
    //   else if (raw == IR_BTN_LEFT) {/* currentCommand = 12; */}
    //   else if (raw == IR_BTN_RIGHT){/* currentCommand = 13; */}
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

            case 6:
                Serial.println("purr() start");
                IrReceiver.stop();        // undvik timer-krockar med tone()
                purr(1500);               // spinn i 1.5 s (ändra efter smak)
                IrReceiver.start();
                Serial.println("purr() end");
                break;

            case 7: // chirp
                Serial.println("chirp()");
                IrReceiver.stop();
                chirp(240);
                IrReceiver.start();
                break;

            case 8: // chatter
                Serial.println("chatter()");
                IrReceiver.stop();
                chatter(10, 55); // 10 hack, ~55 ms styck
                IrReceiver.start();
                break;

            case 9: // growl
                Serial.println("growl()");
                IrReceiver.stop();
                growl(800);
                IrReceiver.start();
                break;
            
            case 14:
                Serial.println("caterwaul() start");
                IrReceiver.stop();
                caterwaul(2000);          // 2 s ylande
                IrReceiver.start();
                Serial.println("caterwaul() end");
                break;
                       break;
      case 20:
        Serial.println("hopAndPlaySafe()");
        hopAndPlaySafe();
        break;
                
            case 10:
                Serial.println("move forward!");
                moveForward();
                break;

            case 11:
                Serial.println("move forward!");
                moveStop();
                break;
        }

            // case 10..13: lägg motor/servo-styrning här om du vill
        currentCommand = 0;  // viktigt: nollställ
    }
}
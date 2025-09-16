#include <Arduino.h>
#line 1 "C:\\Users\\segunyb1\\MeowBot\\MeowBot\\MeowBot.ino"
#define RECV_PIN 11
#define BUZZER_PIN 8
#include <IRremote.h>
#include "sound.h"

IRrecv irrecv(RECV_PIN);
// IrReceiverStruct *irReceiver = &IrReceiver;

#line 9 "C:\\Users\\segunyb1\\MeowBot\\MeowBot\\MeowBot.ino"
void setup();
#line 17 "C:\\Users\\segunyb1\\MeowBot\\MeowBot\\MeowBot.ino"
void loop();
#line 9 "C:\\Users\\segunyb1\\MeowBot\\MeowBot\\MeowBot.ino"
void setup() {
  Serial.begin(115000);
  Serial.println("Test");
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Starta mottagaren
}

volatile int currentCommand = 0;

void loop() {
    if (IrReceiver.decode()) {
        Serial.print("IR command: ");
        Serial.println(IrReceiver.decodedIRData.command, HEX);
        int prevCommand = currentCommand;
        currentCommand = IrReceiver.decodedIRData.command;
        if (prevCommand != currentCommand) {
            Serial.print("currentCommand ändrad till: ");
            Serial.println(currentCommand);
        }
        IrReceiver.resume(); // Ta emot nästa värde
    }
    if (currentCommand != 0) {
        Serial.print("currentCommand: ");
        Serial.println(currentCommand);
    }
    if (currentCommand != 0) {
        switch(currentCommand) {
            case 4:
                Serial.println("meow() start");
                meow();
                Serial.println("meow() end");
                IrReceiver.resume();
                break;
            case 5:
                Serial.println("hiss() start");
                hiss(600);
                Serial.println("hiss() end");
                IrReceiver.resume();
                break;
            // Lägg till fler kommandon här
            default:
                break;
        }
    }
}

void meow(); // Gör denna avbrytbar med currentCommand

void hiss(unsigned long ms);


#line 1 "C:\\Users\\segunyb1\\MeowBot\\MeowBot\\sound.ino"
// Funktionerna meow och hiss är nu flyttade till sound.cpp


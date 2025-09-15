#include <Arduino.h>
#line 1 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\test-2\\test-2.ino"
#include <IRremote.h>

#define RECV_PIN 11 // Ändra till din IR-mottagarens pin
#define BUZZER_PIN 8

IRrecv irrecv(RECV_PIN);
// IrReceiverStruct *irReceiver = &IrReceiver;

#line 9 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\test-2\\test-2.ino"
void setup();
#line 14 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\test-2\\test-2.ino"
void loop();
#line 25 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\test-2\\test-2.ino"
void meow();
#line 9 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\test-2\\test-2.ino"
void setup() {
  Serial.begin(115000);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK); // Starta mottagaren
}

void loop() {
    if (IrReceiver.decode()) {
        Serial.println(IrReceiver.decodedIRData.command, HEX);
        IrReceiver.resume(); // Ta emot nästa värde
    }

    if(IrReceiver.decodedIRData.command == 4){
        meow();
    }
}

void meow(){
    for (int m = 0; m < 4; m++) {
        for (int freq = 1200; freq >= 600; freq -= 5) {
            tone(BUZZER_PIN, freq);
            delay(3);
        }
        noTone(BUZZER_PIN);

        if(m < 3){
            delay (400); // Kort paus mellan varje "meow"
        }
    }
}



// --- Ultraljud ---
const int TRIG = 8;
const int ECHO = 9;

// --- Motorpinnar (anpassa efter din drivrutin) ---
const int IN1 = 5;   // Vänster motor +
const int IN2 = 6;   // Vänster motor -
const int IN3 = 10;  // Höger motor +
const int IN4 = 11;  // Höger motor -

// --- Ljud ---
const int BUZZ = 4;

// --- Avståndströsklar (cm) ---
const int STOP_CM      = 20;  // <= 20 cm: STOPP (och fräs)
const int SNEAK_LOW    = 30;  // 30–50 cm: smyg
const int SNEAK_HIGH   = 50;

// --- Farter ---
const int SPEED_NORMAL = 200; // 0–255
const int SPEED_SNEAK  = 110;

// --- Beteendeparametrar ---
const int BACKUP_MS      = 250;   // backa lite när vi stannar
const int TURN_MS        = 250;   // och sväng undan
const int HISS_MS        = 600;   // längd på fräs
const int HISS_COOLDOWN  = 1500;  // minsta tid mellan fräs (ms)

unsigned long lastHiss = 0;

// ====== Hjälpfunktioner ======
long distanceCM() {
  // median av 3 mätningar för stabilitet
  long r[3];
  for (int i = 0; i < 3; i++) {
    digitalWrite(TRIG, LOW);  delayMicroseconds(2);
    digitalWrite(TRIG, HIGH); delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    unsigned long dur = pulseIn(ECHO, HIGH, 25000UL); // ~4 m timeout
    long cm = (dur == 0) ? 500 : (dur * 0.0343 / 2.0);
    r[i] = cm;
    delay(10);
  }
  if (r[1] < r[0]) swap(r[0], r[1]);
  if (r[2] < r[1]) swap(r[1], r[2]);
  if (r[1] < r[0]) swap(r[0], r[1]);
  return r[1];
}

void motorsForward(int spd) {
  analogWrite(IN1, spd);  analogWrite(IN2, 0);
  analogWrite(IN3, spd);  analogWrite(IN4, 0);
}
void motorsBackward(int spd) {
  analogWrite(IN1, 0);    analogWrite(IN2, spd);
  analogWrite(IN3, 0);    analogWrite(IN4, spd);
}
void motorsLeft(int spd) {     // enkel plats-sväng
  analogWrite(IN1, 0);    analogWrite(IN2, spd);
  analogWrite(IN3, spd);  analogWrite(IN4, 0);
}
void motorsStop() {
  analogWrite(IN1, 0); analogWrite(IN2, 0);
  analogWrite(IN3, 0); analogWrite(IN4, 0);
}

// Emulera "fräs" genom snabbt varierande frekvens (vitbrus-lik känsla)
void hiss(unsigned long ms) {
  unsigned long t0 = millis();
  while (millis() - t0 < ms) {
    int f = random(3000, 6000); // slumpa ton inom övre mellanregister
    tone(BUZZ, f, 20);
    delay(15);
  }
  noTone(BUZZ);
}

// ====== Setup/Loop ======
void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  motorsStop();
  randomSeed(analogRead(A0)); // för hiss-slump
  delay(200);
}

void loop() {
  long d = distanceCM();

  if (d <= STOP_CM) {
    motorsStop();

    // Fräs en gång per cooldown
    if (millis() - lastHiss > HISS_COOLDOWN) {
      hiss(HISS_MS);
      lastHiss = millis();
    }

    // Backa och sväng undan lite (katt blir "rädd")
    if (BACKUP_MS > 0) {
      motorsBackward(180);
      delay(BACKUP_MS);
    }
    motorsLeft(180);
    delay(TURN_MS);
    motorsStop();
    delay(120); // liten paus

  } else if (d > STOP_CM && d <= SNEAK_HIGH) {
    // Smygläge: kör långsamt; närmare STOP_CM -> ännu försiktigare
    // Linjär nedskalning mellan 30–50 cm (klamra 80–SPEED_SNEAK)
    int spd = SPEED_SNEAK;
    if (d < SNEAK_HIGH) {
      float k = float(d - SNEAK_LOW) / float(SNEAK_HIGH - SNEAK_LOW); // 0..1
      k = constrain(k, 0.0, 1.0);
      spd = max(80, int(80 + k * (SPEED_SNEAK - 80)));
    }
    motorsForward(spd);

  } else {
    // Fritt fram: normal fart
    motorsForward(SPEED_NORMAL);
  }

  delay(30);
}

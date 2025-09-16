#line 1 "C:\\Users\\SEIDFUN\\Desktop\\MeowBot\\MeowBot\\sound.h"
#ifndef SOUND_H
#define SOUND_H

void meow();
void hiss(unsigned long ms);

void purr(unsigned long ms = 1200);

void chirp(uint16_t durMs = 220);              // kort “prrt!”
void chatter(uint16_t reps = 8, uint16_t rateMs = 55); // “krr-krr…”
void growl(uint16_t durMs = 700);              // lågt morr

void caterwaul(uint16_t durMs = 1800);  // långt, ylande jam

#endif // SOUND_H

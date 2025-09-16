#ifndef CLAP_H
#define CLAP_H

enum ClapEvent { NONE, SINGLE_CLAP, DOUBLE_CLAP };

void clapSetup(int micPin);
ClapEvent updateClapDetector();

#endif

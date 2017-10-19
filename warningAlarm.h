#include "bool.h"

#ifndef WARNINGALARM_H_
#define WARNINGALARM_H_
void alarm(void* data);
void checkWarnings(void* data);
void annunciate(void* data);
void checkPulse(unsigned int* pulse, Bool* pulseLow, int index);
void checkBp(unsigned int* bpBuf, Bool* bpHigh, int index);
void checkTemp(unsigned int* temp, Bool* tempHigh, int index);
void enableVisibleAnnunciation();
void disableVisibleAnnunciation();

#endif
#include "bool.h"

#ifndef WARNINGALARM_H_
#define WARNINGALARM_H_
void alarm(void* data);
void checkWarnings(void* data);
void checkPulse(unsigned int* pulse, Bool* pulseLow);
void checkBp(unsigned int* sys, unsigned int* dia, Bool* bpHigh);
void checkTemp(unsigned int* temp, Bool* tempHigh);

#endif
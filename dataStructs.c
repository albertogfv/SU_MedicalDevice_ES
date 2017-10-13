#include <stdio.h>
#include "bool.h"

typedef struct
{
	unsigned int temperatureRaw;
    unsigned int systolicPressRaw;
 	unsigned int diastolicPressRaw;
 	unsigned int pulseRateRaw;
    unsigned int countCalls;
    unsigned int sysComplete;
    unsigned int diaComplete;
    int tempDirection;
    int prDirection;
} measurement;

#define INIT_MEASUREMENT(X) measurement X ={75,80,80,2,0,0,0,1,1};

typedef struct
{
	unsigned char* tempCorrected;
    unsigned char* systolicPressCorrected;
	unsigned char* diastolicPressCorrected;
	unsigned char* pulseRateCorrected;
}display;

#define INIT_DISPLAY(X) display X ={NULL,NULL,NULL,NULL};

typedef struct
{
	unsigned short batteryState;
}status;

#define INIT_STATUS(X) status X ={'\0'};

typedef struct
{
	unsigned char bpOutOfRange;
	unsigned char tempOutOfRange;
	unsigned char pulseOutOfRange;
}alarms;
#define INIT_ALARMS(X) alarms X ={'\0','\0','\0'};

typedef struct 
{
	Bool bpHigh;
	Bool tempHigh;
	Bool pulseLow;
    Bool annunciate;
    unsigned int count;
}warning;
#define INIT_WARNING(X) warning X={FALSE,FALSE,FALSE,FALSE,0};

typedef struct{
	unsigned int globalCounter;
}scheduler;
#define INIT_SCHEDULER(X) scheduler X={0};

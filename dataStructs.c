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
//Change the structs to use arrays. bloodpress has both systolic and diastolic
typedef struct
{
    unsigned int temperatureRawBuf[8];
    unsigned int bloodPressRawBuf[16];
    unsigned int pulseRateRawBuf[8];
    unsigned int countCalls;
    unsigned int sysComplete;
    unsigned int diaComplete;
    int tempDirection;
    int prDirection;
} measurement2;
#define INIT_MEASUREMENT2(X) measurement2 X ={75,80,80,2,0,0,0,1,1};



typedef struct
{
	unsigned char* tempCorrected;
        unsigned char* systolicPressCorrected;
	unsigned char* diastolicPressCorrected;
	unsigned char* pulseRateCorrected;
}display;

typedef struct
{
	unsigned char* tempCorrectedBuf[8];
        unsigned char* bloodPressCorrectedBuf[16];
	unsigned char* pulseRateCorrectedBuf[8];
}display2;

#define INIT_DISPLAY(X) display X ={NULL,NULL,NULL,NULL};
#define INIT_DISPLAY2(X) display2 X ={NULL,NULL,NULL,NULL};

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

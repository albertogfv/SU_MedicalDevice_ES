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
#define INIT_MEASUREMENT2(X) measurement2 X ={{55,NULL,NULL,NULL,NULL,NULL,NULL,NULL},{80,NULL,NULL,NULL,NULL,NULL,NULL,NULL,80,NULL,NULL,NULL,NULL,NULL,NULL,NULL},{0,NULL,NULL,NULL,NULL,NULL,NULL,NULL},0,0,0,1,1};

// Project 2 display struct
typedef struct
{
  unsigned char* tempCorrected;
  unsigned char* systolicPressCorrected;
  unsigned char* diastolicPressCorrected;
  unsigned char* pulseRateCorrected;
}display;
#define INIT_DISPLAY(X) display X ={NULL,NULL,NULL,NULL};

// Project 3 display struct
typedef struct
{
  unsigned char tempCorrectedBuf[8];
  unsigned char bloodPressCorrectedBuf[16];
  unsigned char pulseRateCorrectedBuf[8];
}display2;
#define INIT_DISPLAY2(X) display2 X ={NULL,NULL,NULL};

// Struct holding status task data
typedef struct
{
  unsigned short batteryState;
}status;
#define INIT_STATUS(X) status X ={200};

// Struct holding alarm data
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
  unsigned int led;
  unsigned long previousCount;
  const long pulseFlash;
  const long tempFlash;
  const long bpFlash;
}warning;
#define INIT_WARNING(X) warning X={FALSE,FALSE,FALSE,FALSE,0,0,20,10,5};

typedef struct{
  unsigned int globalCounter;
}scheduler;
#define INIT_SCHEDULER(X) scheduler X={0};

// Datastruct for keypad data
typedef struct{
  unsigned short mode;
  unsigned short measurementSelection;
  unsigned short scroll;
  unsigned short selectChoice;
  unsigned short alarmAcknowledge;
}keypad;
#define INIT_KEYPAD(X) keypad X={0,0,0,0,0};


typedef struct MyStruct 
{

    void (*taskPtr)(void*);
    void* taskDataPtr;
    struct MyStruct* next;
    struct MyStruct* prev;
}
TCB;


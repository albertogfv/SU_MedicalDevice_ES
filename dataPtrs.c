#include "bool.h"
typedef struct //Holds pointers to the variables: 
{
      unsigned int* temperatureRawPtr;
      unsigned int* systolicPressRawPtr;
      unsigned int* diastolicPressRawPtr;
      unsigned int* pulseRateRawPtr;
      unsigned int* countCallsPtr;
      //Variables to simulate data measurements
      unsigned int* sysCompletePtr;
      unsigned int* diaCompletePtr;
      int* tempDirectionPtr;
      int* prDirectionPtr;
} measureData;

typedef struct //Holds pointers to the variables: 
{
      unsigned int* temperatureRawPtr;
      unsigned int* systolicPressRawPtr;
      unsigned int* diastolicPressRawPtr;
      unsigned int* pulseRateRawPtr;
      unsigned int* countCallsPtr;
      //Variables to simulate data measurements
      unsigned int* sysCompletePtr;
      unsigned int* diaCompletePtr;
      int* tempDirectionPtr;
      int* prDirectionPtr;
} measureData2;

typedef struct 
{
	
  unsigned int* temperatureRawPtr;
  unsigned int* systolicPressRawPtr;
  unsigned int* diastolicPressRawPtr; 
  unsigned int* pulseRateRawPtr;
  unsigned char** tempCorrectedPtr;
  unsigned char** sysPressCorrectedPtr; 
  unsigned char** diasCorrectedPtr; 
  unsigned char** prCorrectedPtr;
}computeData;

typedef struct 
{
	unsigned char** tempCorrectedPtr;
	unsigned char** sysCorrectedPtr;
	unsigned char** diasCorrectedPtr;
	unsigned char** prCorrectedPtr;
	unsigned short* batteryStatePtr;
}displayData;

typedef struct
{
	unsigned int* temperatureRawPtr;
  unsigned int* systolicPressRawPtr;
  unsigned int* diastolicPressRawPtr;
  unsigned int* pulseRateRawPtr;
	unsigned short* batteryStatePtr;
  unsigned char* bpOutOfRangePtr;
	unsigned char* tempOutOfRangePtr;
	unsigned char* pulseOutOfRangePtr;
  Bool* bpHighPtr;
	Bool* tempHighPtr;
	Bool* pulseLowPtr;
  Bool* annunciatePtr;
  unsigned int* countPtr;
} warningAlarmData;

typedef struct 
{
	unsigned short* batteryStatePtr;
}statusData;

typedef struct
{
	unsigned int* globalCounterPtr;
}schedulerData;

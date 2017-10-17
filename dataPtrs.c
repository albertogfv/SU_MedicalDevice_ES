#include "bool.h"

// Holds pointers to the variables associated with measure task:
typedef struct  
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

// Holds pointers to the variables associated with measure task:
typedef struct
{
  unsigned int* temperatureRawBufPtr;
  unsigned int* bloodPressRawBufPtr;
  unsigned int* pulseRateRawBufPtr;
  unsigned int* countCallsPtr;
  //Variables to simulate data measurements
  unsigned int* sysCompletePtr;
  unsigned int* diaCompletePtr;
  int* tempDirectionPtr;
  int* prDirectionPtr;
  unsigned short* measurementSelectionPtr;
} measureData2;

// Holds pointers to the variables associated with compute task:
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

// Holds pointers to the variables associated with compute task:
typedef struct 
{
  unsigned int* temperatureRawBufPtr;
  unsigned int* bloodPressRawBufPtr;
  unsigned int* pulseRateRawBufPtr;
  unsigned char* tempCorrectedBufPtr;
  unsigned char* bloodPressCorrectedBufPtr;
  unsigned char* pulseRateCorrectedBufPtr;
  unsigned short* measurementSelectionPtr;
}computeData2;

// Holds pointers to the variables associated with display task:
typedef struct 
{
  unsigned char** tempCorrectedPtr;
  unsigned char** sysCorrectedPtr;
  unsigned char** diasCorrectedPtr;
  unsigned char** prCorrectedPtr;
  unsigned short* batteryStatePtr;
}displayData;

// Holds pointers to the variables associated with display task:
typedef struct 
{
  unsigned short* modePtr;
  unsigned char* tempCorrectedBufPtr;
  unsigned char* bloodPressCorrectedBufPtr;
  unsigned char* pulseRateCorrectedBufPtr;
  unsigned short* batteryStatePtr;
}displayData2;

// Holds pointers to the variables associated with warning/alarm task:
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

// Holds pointers to the variables associated with status task:
typedef struct 
{
  unsigned short* batteryStatePtr;
}statusData;

// Holds pointers to the variables associated with scheduler task:
typedef struct
{
  unsigned int* globalCounterPtr;
}schedulerData;

// Holds pointers to the variables associated with keypad task:
typedef struct
{
  unsigned short* modePtr;
  unsigned short* measurementSelectionPtr;
  unsigned short* scrollPtr;
  unsigned short* selectChoicePtr;
  unsigned short* alarmAcknowledge;
}keypadData;

// Holds pointers to the variables associated with communications task:
typedef struct
{
  unsigned char* tempCorrectedBufPtr;
  unsigned char* bloodPressCorrectedBufPtr;
  unsigned char* prCorrectedBufPtr;
  unsigned short* batteryStatePtr;
}communicationsData;

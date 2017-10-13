/*
Citation:
Code to enable and disable light referenced from Blinky.c from StellarisWare example package.
*/

#include "inc/lm3s8962.h"
#include "warningAlarm.h"
#include "dataPtrs.c"
#include <stdlib.h>
#include <stdio.h>
#include "bool.h"
#include "delays.h"

/*
Function alarm
Input: pointer to alarmData
Output Null
Do: Checks if vitals are out of range
*/
void alarm(void *data)
{
  //warningAlarmData * alarm = (warningAlarmData*) data;
  checkWarnings(data);
}

/*
Function checkWarnings
Input pointer to alarmData
Output Null
Do: Checks raw measurements against ranges and annunciates accordingly
*/

void checkWarnings(void *data)
{
  warningAlarmData * alarm = (warningAlarmData*) data;
  unsigned int* temp = (*alarm).temperatureRawPtr;
  unsigned int* sys = (*alarm).systolicPressRawPtr;
  unsigned int* dia = (*alarm).diastolicPressRawPtr;
  unsigned int* pulse = (*alarm).pulseRateRawPtr;
  unsigned char* battery = (*alarm).batteryStatePtr;
  unsigned char* bpOut = (*alarm).bpOutOfRangePtr;
  unsigned char* tempOut = (*alarm).tempOutOfRangePtr;
  unsigned char* pulseOut = (*alarm).pulseOutOfRangePtr;
  Bool* bpHigh = (*alarm).bpHighPtr;
  Bool* tempHigh = (*alarm).tempHighPtr;
  Bool* pulseLow = (*alarm).pulseLowPtr;
  Bool* annun = (*alarm).annunciatePtr;
  unsigned int* count = (*alarm).countPtr;
  
  // Increment count for number of tasks executed
  (*count) += 5;

  //printf("count: %i", (*count));
  printf("Warning Alarm: %i\n", (*temp));
  
  // Check vitals against prescribed ranges. Set warnings accordingly
  checkTemp(temp, tempHigh);
  checkBp(sys, dia, bpHigh);
  checkPulse(pulse, pulseLow);
  
  if(*(pulseLow))
    printf("pulse low: ");
  
 
}



/*
Function checkTemp
Input: pointer to temperatureRaw, pointer to tempHigh
Output: Null
Do: Checks if values are within normal range and sets bool accordingly.
*/
void checkTemp(unsigned int* temp, Bool* tempHigh)
{
  // Check if temperature is in range. Set warning accordingly
  if((*temp) < 96.98 || (*temp) > 100.04)
  {
    tempHigh = (Bool*)TRUE;
  } 
  else
  {
    tempHigh = (Bool*)FALSE;
  }
}

/*
Function checkBp
Input: pointer to systolicRaw, pointer to diastolicRaw, pointer to bpHigh
Output: Null
Do: Checks if values are within normal range and sets bool accordingly.
*/
void checkBp(unsigned int* sys, unsigned int* dia, Bool* bpHigh)
{
  // Check if blood pressure is in range.  Set warnings accordingly
  if ((*sys) > 120 || (*dia) > 80)
  {
    bpHigh = (Bool*)TRUE; 
  }
  else
  {
    bpHigh = (Bool*)FALSE;
  }
}

/*
Function checkPulse
Input: pointer to pulseRateRaw, pointer to pulseLow
Output: Null
Do: Checks if values are within normal range and sets bool accordingly.
*/
void checkPulse(unsigned int* pulse, Bool* pulseLow)
{
  printf("Here: %i\n", 1);
  // Check if pulse rate is in range. Set warning accordingly.
  if ((int)(*pulse) < 60)
  {
    *pulseLow = *(Bool*)TRUE;
    printf("Here: %i\n", 1);
  }
  else
  {
    *pulseLow = *(Bool*)FALSE;
  }
}
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
#include "systemTimeBase.h"


/*
Function alarm
Input: pointer to alarmData
Output Null
Do: Checks if vitals are out of range
*/
void alarm(void *data)
{
  if(globalCounter % 50 < 5)
  {  
    //warningAlarmData * alarm = (warningAlarmData*) data;
    checkWarnings(data);
  }

    annunciate(data);

}

/*
Function checkWarnings
Input pointer to alarmData
Output Null
Do: Checks raw measurements against ranges and annunciates accordingly
*/

void checkWarnings(void *data)
{
  warningAlarmData2 * alarm = (warningAlarmData2*) data;
  
  //find the current index of the array based on call count. 
  unsigned int index = ((*(alarm->countCallsPtr)) % 8);
  
  unsigned int* tempBuf = (*alarm).temperatureRawBufPtr;
  unsigned int* bpBuf = (*alarm).bloodPressRawBufPtr;
  unsigned int* pulseBuf = (*alarm).pulseRateRawBufPtr;
  unsigned short* battery = (*alarm).batteryStatePtr;
  unsigned char* bpOut = (*alarm).bpOutOfRangePtr;
  unsigned char* tempOut = (*alarm).tempOutOfRangePtr;
  unsigned char* pulseOut = (*alarm).pulseOutOfRangePtr;
  Bool* bpHigh = (*alarm).bpHighPtr;
  Bool* tempHigh = (*alarm).tempHighPtr;
  Bool* pulseLow = (*alarm).pulseLowPtr;
  Bool* annun = (*alarm).annunciatePtr;
  

  // Check vitals against prescribed ranges. Set warnings accordingly
  checkTemp(tempBuf, tempHigh, index);
  checkBp(bpBuf, bpHigh, index);
  checkPulse(pulseBuf, pulseLow, index);
}



/*
Function checkTemp
Input: pointer to temperatureRaw, pointer to tempHigh
Output: Null
Do: Checks if values are within normal range and sets bool accordingly.
*/
void checkTemp(unsigned int* temp, Bool* tempHigh, int index)
{
  //printf("checkTemp: %i \n", temp[index]);
  // Check if temperature is in range. Set warning accordingly
  if((temp[index]) < 41.46 || (temp[index]) > 43.73)
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
void checkBp(unsigned int* bpBuf, Bool* bpHigh, int index)
{
  // Check if blood pressure is in range.  Set warnings accordingly
  if ((bpBuf[index]) > 60.5 || (bpBuf[index]) < 55.5 || (bpBuf[index + 8]) > 49.33 || (bpBuf[index + 8]) < 42.67)
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
void checkPulse(unsigned int* pulse, Bool* pulseLow, int index)
{
  //printf("Here: %i\n", 1);
  // Check if pulse rate is in range. Set warning accordingly.
  if ((int)(*pulse) < 60)
  {
    *pulseLow = *(Bool*)TRUE;
    //printf("Here: %i\n", 1);
  }
  else
  {
    *pulseLow = *(Bool*)FALSE;
  }
}

/*
Function: annunciate
Input: warning data
Output: Flashing of LED on board
Do: Flashes LED at rate per specific warning.
*/
void annunciate(void *data)
{
  warningAlarmData2 * alarm = (warningAlarmData2*) data;
  unsigned int* led = (*alarm).ledPtr;
  unsigned long* previousCount = (*alarm).previousCountPtr;
  const long pulseFlash = *(alarm->pulseFlashPtr);
  const long tempFlash = *(alarm->tempFlashPtr);
  const long bpFlash = *(alarm->bpFlashPtr);
  
  // Flash at the correct rate for each warning.
      if(*(alarm->pulseLowPtr))
      { 
        if(globalCounter - (*previousCount) >= pulseFlash)
        {
          (*previousCount) = globalCounter;
          printf("PREVIOUS COUNT: %i \n", (*previousCount));
          printf("PULSELOW LED \n\n");
          if((*led) == 1)
          {
            //printf("LED OFF \n\n");
            disableVisibleAnnunciation();
            (*led) = 0;
          }
          else
          {
            //printf("LED ON \n\n");
            enableVisibleAnnunciation();
            (*led) = 1;
          }
        }    
      }
      else if (*(alarm->tempHighPtr))
      {
        if(globalCounter - (*previousCount) >= tempFlash)
        { 
          (*previousCount) = globalCounter;
          printf("TEMPHIGH LED \n\n");
          if((*led) == 1)
          {
            disableVisibleAnnunciation();
            (*led) = 0;
          }
          else
          {
            enableVisibleAnnunciation();  
            (*led) = 1;
          }
        }
      }
      else if (*(alarm->bpHighPtr))
      {
        if(globalCounter - (*previousCount) >= bpFlash)
        {
          (*previousCount) = globalCounter;
          printf("BPHIGH LED \n\n");
          if((*led) == 1)
          {
            disableVisibleAnnunciation();
            (*led) = 0;
          }
          else
          {
            enableVisibleAnnunciation();
            (*led) = 1;
          }
        }
      }
 
}

/*
Function enableVisibleAnnunciation
Input: N/A
Output: Null
Do: Turns on LED on StellarisWare board
*/
void enableVisibleAnnunciation()
{
  // Enable the GPIO port that is used for the on-board LED.
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

  // Enable the GPIO pin for the LED (PF0).  Set the direction as output, and
  // enable the GPIO pin for digital function.
  GPIO_PORTF_DIR_R = 0x01;
  GPIO_PORTF_DEN_R = 0x01;

  // Turn on the LED.
  GPIO_PORTF_DATA_R |= 0x01; 
}

/*
Function disableVisibleAnnunciation
Input: N/A
Output: Null
Do: Turns off LED on StellarisWare board
*/

void disableVisibleAnnunciation()
{
  // Enable the GPIO pin for the LED (PF0).  Set the direction as output, and
  // enable the GPIO pin for digital function. 
  GPIO_PORTF_DIR_R = 0x01;
  GPIO_PORTF_DEN_R = 0x01;

  // Turn off the LED.
  GPIO_PORTF_DATA_R &= ~(0x01);
}


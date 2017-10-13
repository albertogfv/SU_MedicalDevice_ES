#include "drivers/rit128x96x4.h"
#include <stdio.h>
#include <string.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "dataStructs.c"
#include "measureTask.h"
#include "computeTask.h"
#include "warningAlarm.h"
#include "delays.h"
//#include "displayTask.h"
//#include "dataPtrs.c"
#include "dataPtrs.h"
#include "displayTask.h"
#include "inc/lm3s8962.h"

#define KBINT 0x3;	//he kb will interrupt on interrupt 3

//  Declare the globals

INIT_MEASUREMENT(m1);
INIT_DISPLAY(d1);
INIT_STATUS(s1);
INIT_ALARMS(a1);
INIT_WARNING(w1);
INIT_SCHEDULER(c1);

//Connect pointer structs to data
measureData mPtrs = 
{     &m1.temperatureRaw,
      &m1.systolicPressRaw,
      &m1.diastolicPressRaw,
      &m1.pulseRateRaw,
      &m1.countCalls,
      &m1.sysComplete,
      &m1.diaComplete,
      &m1.tempDirection,
      &m1.prDirection
};

computeData cPtrs=
{
      &m1.temperatureRaw,
      &m1.systolicPressRaw,
      &m1.diastolicPressRaw,
      &m1.pulseRateRaw,
      &d1.tempCorrected,
      &d1.systolicPressCorrected, 
      &d1.diastolicPressCorrected, 
      &d1.pulseRateCorrected
};

displayData dPtrs={
      &d1.tempCorrected,
      &d1.systolicPressCorrected, 
      &d1.diastolicPressCorrected, 
      &d1.pulseRateCorrected,
      &s1.batteryState
};

warningAlarmData wPtrs={
      &m1.temperatureRaw,
      &m1.systolicPressRaw,
      &m1.diastolicPressRaw,
      &m1.pulseRateRaw,
      &s1.batteryState,
      &a1.bpOutOfRange,
      &a1.tempOutOfRange,
      &a1.pulseOutOfRange,
      &w1.bpHigh,
      &w1.tempHigh,
      &w1.pulseLow,
      &w1.annunciate,
      &w1.count
};

statusData sPtrs={
  
  &s1.batteryState
};

schedulerData schedPtrs={
 
  &c1.globalCounter
};

//  Declare a TCB structure

typedef struct 
{
      void* taskDataPtr;
      void (*taskPtr)(void*);
}
TCB;

//Declare the prototypes for the tasks
void compute(void* data);
void measure(void* data);
void stat(void* data);
void alarm(void* data);
void disp(void* data);
void schedule(void* data);
void enableVisibleAnnunciation();
void disableVisibleAnnunciation();

void main(void)
{
	TCB scheduleT;
        
    scheduleT.taskPtr = schedule;
    scheduleT.taskDataPtr = (void*)&schedPtrs;
    
    TCB* aTCBPtr;
	
	aTCBPtr = &scheduleT;
	aTCBPtr->taskPtr((aTCBPtr->taskDataPtr) ); 
                
	return;

}


void schedule(void* data)
{
        int toggle =0;
        int start =0;
        int i=0;
        TCB* queue[7];	          //  declare queue as an array of pointers to TCBs
     
	    //  Declare some TCBs 
	    TCB displayT;
	    TCB measureT;
	    TCB statusT;
        TCB computeT;
        TCB warningT;
        
	    //  Declare a working TCB pointer
	
        TCB* aTCBPtr;

	    //Initialize the TCBs

	    displayT.taskPtr = disp;
        displayT.taskDataPtr = (void*)&dPtrs;

	    measureT.taskPtr = measure;
        measureT.taskDataPtr = (void*)&mPtrs;
	
        statusT.taskPtr = stat;
        statusT.taskDataPtr = (void*)&sPtrs;

        computeT.taskPtr = compute;
        computeT.taskDataPtr = (void*)&cPtrs;

        warningT.taskPtr = alarm;
        warningT.taskDataPtr = (void*)&wPtrs;
        
        //Initialize the task queue
	    queue[0] = &measureT;
	    queue[1] = &warningT;
        queue[2] = &statusT;
        queue[3] = &computeT;
        queue[4] = &displayT;
        //queue[5] = &scheduleT;
	    //queue[6] = &displayTask;

	   
    
    schedulerData*tempA=(schedulerData*)data;
    unsigned int*clock =(*tempA).globalCounterPtr;
    enableVisibleAnnunciation();
    int led = 1;
    
    //	Schedule and dispatch the tasks
	
    while(1)
	{
                
                
                if(toggle==1){
                    
                  
                  // Flash at the correct rate for each warning.
                  if(*(wPtrs.pulseLowPtr))
                  { 
                    if((*clock % 200) == 0)
                    {
                      if(led == 1)
                      {
                        disableVisibleAnnunciation();
                        led = 0;
                      }
                      else
                      {
                        enableVisibleAnnunciation();
                        led = 1;
                      }
                    }    
                  }
                  else if (*(wPtrs.tempHighPtr))
                  {
                    if((*clock % 100) == 0)
                      if(led == 1)
                      {
                        disableVisibleAnnunciation();
                        led = 0;
                      }
                      else
                      {
                        enableVisibleAnnunciation();  
                        led = 1;
                      }
                  }
                  else if (*(wPtrs.bpHighPtr))
                  {
                    if((*clock % 50) == 0)
                    {
                      if(led == 1)
                      {
                        disableVisibleAnnunciation();
                        led = 0;
                      }
                      else
                      {
                        enableVisibleAnnunciation();
                        led = 1;
                      }
                    }
                  }
                  
                  delay(100);
                  *clock=*clock +1;
                  
                  if(*clock >= start+500){ 
                    toggle =0;
                  }
                }
                else{  
                    
                    aTCBPtr = queue[i];
		            aTCBPtr->taskPtr((aTCBPtr->taskDataPtr) );
		    
                    *clock =*clock+1;
                     delay(100);
                    i = (i+1)%5;
                    
                  
                    if (i==0){
                        toggle =1;
                        start= *clock;
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

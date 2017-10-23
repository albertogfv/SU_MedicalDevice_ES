#include "drivers/rit128x96x4.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "dataStructs.c"
#include "measureTask.h"
#include "computeTask.h"
#include "warningAlarm.h"
#include "delays.h"
#include "dataPtrs.h"
#include "displayTask.h"
#include "inc/lm3s8962.h"
#include "systemTimeBase.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "buttontest.h"


//  Declare the globals

INIT_MEASUREMENT(m1);
INIT_MEASUREMENT2(m2);
INIT_DISPLAY(d1);
INIT_DISPLAY2(d2);
INIT_STATUS(s1);
INIT_ALARMS(a1);
INIT_WARNING(w1);
INIT_SCHEDULER(c1);
INIT_KEYPAD(k1);

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

measureData2 mPtrs2 = 
{     m2.temperatureRawBuf,
      m2.bloodPressRawBuf,
      m2.pulseRateRawBuf,
      &m2.countCalls,
      &m2.sysComplete,
      &m2.diaComplete,
      &m2.tempDirection,
      &m2.prDirection
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

computeData2 cPtrs2=
{
      m2.temperatureRawBuf,
      m2.bloodPressRawBuf,
      m2.pulseRateRawBuf,
      d2.tempCorrectedBuf,
      d2.bloodPressCorrectedBuf,
      d2.pulseRateCorrectedBuf,
      &k1.measurementSelection,
      &m2.countCalls
};

displayData dPtrs={
      &d1.tempCorrected,
      &d1.systolicPressCorrected, 
      &d1.diastolicPressCorrected, 
      &d1.pulseRateCorrected,
      &s1.batteryState
};

displayData2 dPtrs2={
      d2.tempCorrectedBuf,
      d2.bloodPressCorrectedBuf,
      d2.pulseRateCorrectedBuf,
      &s1.batteryState,
      &m2.countCalls
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
      &w1.led
};
warningAlarmData2 wPtrs2={
      m2.temperatureRawBuf,
      m2.bloodPressRawBuf,
      m2.pulseRateRawBuf,
      &s1.batteryState,
      &a1.bpOutOfRange,
      &a1.tempOutOfRange,
      &a1.pulseOutOfRange,
      &w1.bpHigh,
      &w1.tempHigh,
      &w1.pulseLow,
      &w1.annunciate,
      &w1.led,
      &m2.countCalls,
      &w1.previousCount,
      &w1.pulseFlash,
      &w1.tempFlash,
      &w1.bpFlash
};

statusData sPtrs={
  
  &s1.batteryState
};

schedulerData schedPtrs={
 
  &c1.globalCounter
};

//Declare the prototypes for the tasks
void compute(void* data);
void measure(void* data);
void stat(void* data);
void alarm(void* data);
void disp(void* data);
void schedule(void* data);
void buttonTest();

void insert(struct MyStruct* node);
struct MyStruct* head=NULL;
struct MyStruct* tail=NULL;
void delet(struct MyStruct* node);

unsigned volatile int globalCounter = 0;
//*****************************************************************************
//
// Flags that contain the current value of the interrupt indicator as displayed
// on the OLED display.
//
//*****************************************************************************
unsigned long g_ulFlags;

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}
#endif
//*****************************************************************************
//
// The interrupt handler for the first timer interrupt.
//
//*****************************************************************************
void
Timer0IntHandler(void)
{
    //
    // Clear the timer interrupt.
    //
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Update the global counter.
    //
    IntMasterDisable();
    increment();
    //annunciate(&wPtrs2);
    IntMasterEnable();
}

//*****************************************************************************
//
// The interrupt handler for the second timer interrupt.
//
//*****************************************************************************
//void
//Timer0BIntHandler(void)
//{
//    //
//    // Clear the timer interrupt.
//    //
//    TimerIntClear(TIMER0_BASE, TIMER_TIMB_TIMEOUT);
//
//    //
//    // Update the global counter.
//    //
//    IntMasterDisable();
//    annunciate(&wPtrs2);
//    
//    IntMasterEnable();
//}

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
  
    
    // Set the clocking to run directly from the crystal.
    //
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_8MHZ);

      
    
    
    // Enable the peripherals used by this example.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    //
    // Enable processor interrupts.
    //
    IntMasterEnable();

    //
    // Configure the two 32-bit periodic timers.
    //
    TimerConfigure(TIMER0_BASE, TIMER_CFG_32_BIT_PER);
    
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet()/10);

    //
    // Setup the interrupts for the timer timeouts.
    //
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    //
    // Enable the timers.
    //
    TimerEnable(TIMER0_BASE, TIMER_A);
    
    
  int i=0;
  //TCB* queue[7];	    //  declare queue as an array of pointers to TCBs
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
  displayT.taskDataPtr = (void*)&dPtrs2;
  measureT.taskPtr = measure;
  //measureT.taskDataPtr = (void*)&mPtrs;
  //Comment out the above line and use the new line below. You will also need to uncomment some lines in measureTask.c
  measureT.taskDataPtr = (void*)&mPtrs2;
  
  statusT.taskPtr = stat;
  statusT.taskDataPtr = (void*)&sPtrs;

  computeT.taskPtr = compute;
  computeT.taskDataPtr = (void*)&cPtrs2;

  warningT.taskPtr = alarm;
  warningT.taskDataPtr = (void*)&wPtrs2;
  
  //Initialize the task queue
      insert(&measureT);
      insert(&warningT);
      insert(&statusT);
      insert(&computeT);
      insert(&displayT);
      //insert(&scheduleT);

  enableVisibleAnnunciation();
  
  //	Schedule and dispatch the tasks
  
  int previousCount = 0;
      
  
  while(1)
  {   
    
      if(NULL==head && (globalCounter - previousCount >= 50)){
        //printf("\n\n\nSCHEDULING!\n\n\n");
       insert(&measureT);
      insert(&warningT);
      insert(&statusT);
      insert(&computeT);
      insert(&displayT);
      }
	  
      annunciate(&wPtrs2);
      
      if(!(NULL==head))
      {
      aTCBPtr = head;
      aTCBPtr->taskPtr((aTCBPtr->taskDataPtr) );
      delet(head);
      
      //printf("Global Counter: %i \n", globalCounter);
      i = (i+1)%5;
      if(i == 0)
        previousCount = globalCounter;
      }
      
      buttonTest();
  }          
}



void insert(struct MyStruct* node){
    if(NULL==head){
	    head=node;
	    tail=node;
    }
    else
    {
	    tail->next=node;
	    node->prev =tail;
	    tail=node;
    }
	return;
}
	
	


void delet(  struct MyStruct* node){
	if(NULL==head){
		return;
	}
	else if(head==tail){
		head=NULL;
		tail=NULL;
	}
	else if(head==node){
		head= head->next;
	}
	else if(tail==node){
		tail=tail->prev;
	}
	else
	{
		node->prev->next=node->next;
		node->next->prev=node->prev;
		node->next=NULL;
		node->prev=NULL;
	}
	return;

}
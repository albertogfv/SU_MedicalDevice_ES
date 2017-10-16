// Main and measureTask
#include <stdio.h>
#include "measureTask.h"
#include "dataPtrs.h"
#include "bool.h"



void measure(void* data)
{
    //cast the void* data to a measureData struct
    measureData * measureDataPtr = (measureData*) data;
    
    
    //printf("Count Calls = %d \n", (*(*measureDataPtr).countCallsPtr));
  
    // all the print statements were for tracking the output without needing the debugger
    measureTemp(data);
    //printf("Temp Raw = %d \n", *(*measureDataPtr).temperatureRawPtr); 
    measureSysBP(data);
    //printf("sysRaw = %d \n", *(*measureDataPtr).systolicPressRawPtr);
    measureDiaBP(data);
    //printf("diaRaw = %d \n", *(*measureDataPtr).diastolicPressRawPtr);
    measurePR(data);
    //printf("prRaw = %d \n", *(*measureDataPtr).pulseRateRawPtr);
    
    
    //Moved this to after the measurements so we start at index 0
    //increment the count entry
    (*(*measureDataPtr).countCallsPtr)++;
}

/*
Function measureTemp
Input pointer to measureData
Output Null
Do: updates the tempRaw based on algorithm
*/
void measureTemp(void* data){
  measureData* measureDataPtr = (measureData*) data;
  //printf("This is a measureTemp Function \n");
  //Check to see if the temperature is increasing or decreasing
  int* direction = (*measureDataPtr).tempDirectionPtr;
  unsigned int* countCalls = (*measureDataPtr).countCallsPtr;
  unsigned int* tempRaw = (*measureDataPtr).temperatureRawPtr;
  //If temperature is above 50 and increasing swap the direction
  if (50<=*tempRaw && 1 == *direction){
    *direction = -1;
  }
  //If temperature is below 15 and decreasing swap the direction
  else if (15>=*tempRaw && -1 == *direction){  
    *direction = 1;
  }
  // increment or decrement (using the direction value) If even the magnitude is 2 if odd the magnitude is 1
  *tempRaw +=  (*direction) * (((*countCalls + 1) % 2) + 1);
};

/*
Function measureTempArray
Input pointer to measureData
Output Null
Do: updates the tempRaw based on algorithm
*/
void measureTempArray(void* data){
  measureData* measureDataPtr = (measureData*) data;
  //printf("This is a measureTemp Function \n");
  //Check to see if the temperature is increasing or decreasing
  int* direction = (*measureDataPtr).tempDirectionPtr;
  unsigned int* countCalls = (*measureDataPtr).countCallsPtr;
  //Creates a local pointer to the start of the array
  unsigned int* tempRawBuf = (*measureDataPtr).temperatureRawPtr;
  
  //find the current index of the array based on call count. 
  unsigned int index = (*countCalls) %8;
  unsigned int next = (*countCalls +1) %8;
  //If temperature is above 50 and increasing swap the direction
  if (50<=tempRawBuf[index] && 1 == *direction){
    *direction = -1;
  }
  //If temperature is below 15 and decreasing swap the direction
  else if (15>=tempRawBuf[index] && -1 == *direction){  
    *direction = 1;
  }
  // increment or decrement (using the direction value) If even the magnitude is 2 if odd the magnitude is 1
  tempRawBuf[next] +=  (*direction) * (((*countCalls + 1) % 2) + 1);
};

/*
Function measureSysBp
Input pointer to measureData
Output Null
Do: updates the tempRaw based on algorithm
*/
void measureSysBP(void* data){
    measureData* measureDataPtr = (measureData*) data;
    //printf("This is a measureSysBp Function \n");
    //Check to see if the DiaBp is complete and repeat the original proces
    unsigned int* countCalls = (*measureDataPtr).countCallsPtr;
    unsigned int* sysRaw  = (*measureDataPtr).systolicPressRawPtr;
    unsigned int* sysComplete = (*measureDataPtr).sysCompletePtr;
    unsigned int* diaComplete = (*measureDataPtr).diaCompletePtr;
    
    if (1==*diaComplete && *sysRaw>100){
      *sysRaw = 80;
      *diaComplete = 0;
    }
    // If the sysBP <= 100 its not complete so we increment it
    if (100 >= *sysRaw ){
      if  ( (*countCalls % 2) == 0){
        (*sysRaw) +=3;
      }
      else{
        (*sysRaw)-- ;
      }
    }
    // If sysBP > 100 it is complete and we wait til diaCompletes
    if (100 < *sysRaw){
      *sysComplete = 1;
    }
};

/*
Function measureDiaBp
Input pointer to measureData
Output Null
Do: updates the tempRaw based on algorithm
*/
void measureDiaBP(void* data){
  
    measureData* measureDataPtr = (measureData*) data;
    unsigned int* countCalls = (*measureDataPtr).countCallsPtr;
    unsigned int* diaRaw = (*measureDataPtr).diastolicPressRawPtr;
    unsigned int* sysComplete = (*measureDataPtr).sysCompletePtr;
    unsigned int* diaComplete = (*measureDataPtr).diaCompletePtr;
   // printf("This is a measureSysBp Function \n");
  //Check to see if the DiaBp is complete and repeat the original proces
     if (1==*sysComplete && *diaRaw<40){
      *diaRaw = 80;
      *sysComplete = 0;
    }
    // If diastolyic BP is above 40 it is not complete
    if (40 <= *diaRaw){
      if  ( ((*countCalls) % 2) == 0){
        (*diaRaw) -=2;
      }
      else{
        (*diaRaw)++;
      }
    } 
    // diastolyic BP drops below 40 and is complete
    if (40 > *diaRaw){
      *diaComplete = 1;
    }
};


/*
Function measurePr
Input pointer to measureData
Output Null
Do: updates the tempRaw based on algorithm
*/
void measurePR(void* data){
    measureData* measureDataPtr = (measureData*) data;
    
    unsigned int* countCalls = (*measureDataPtr).countCallsPtr;
    unsigned int* prRaw = (*measureDataPtr).pulseRateRawPtr;
    int* direction = (*measureDataPtr).prDirectionPtr;
  //If pulse rate is above 40 and increasing swap the direction
  if (40<=*prRaw && 1 == *direction){
    *direction = -1;
  }
  //If pulseRate is below 15 and decreasing swap the direction
  else if (15>=*prRaw && -1 == *direction){  
    *direction = 1;
  }
  // increment or decrement (using the direction value)
  if (*countCalls % 2  == 0){
    // even
    *prRaw -= *direction;
  }
  //odd
  else {
    *prRaw += (*direction * 3);
  }

}

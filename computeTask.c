#include "dataPtrs.c"
#include "dataStructs.c"
#include "systemTimeBase.h"

/*
void compute(void *data) {

// Recast task argument pointer to task’s data structure type
	computeData*temp=(computeData*)data;
        
        // corrected temp value
        unsigned int* temp1=(*temp).temperatureRawPtr;
        
        unsigned char** temp2=(*temp).tempCorrectedPtr;
	unsigned char* temp3=(unsigned char*)temp2;
        *temp3 = (unsigned char)( 5 + (.76* (*temp1)));
        
        //correct sys pressure
        temp1=(*temp).systolicPressRawPtr;
        
        temp2=(*temp).sysPressCorrectedPtr;
	temp3=(unsigned char*)temp2;
        *temp3 = (unsigned char) (9 + (2* (*temp1)));
        
        //correct diastolic
        temp1=(*temp).diastolicPressRawPtr;
        
        temp2=(*temp).diasCorrectedPtr;
	temp3=(unsigned char*)temp2;
        *temp3 = (unsigned char) (6 + (1.5* (*temp1)));
        
        
        //correct pulse rate
        temp1=(*temp).pulseRateRawPtr;
        
        temp2=(*temp).prCorrectedPtr;
	temp3=(unsigned char*)temp2;
        *temp3 = (unsigned char) (8 + (3* (*temp1)));
        
        
        return;  
}

*/

void compute(void *data)
{
  if(globalCounter % 50 < 5)
  {
  // Cast struct
  computeData2* cData =(computeData2*)data;
  
  //find the current index of the array based on call count. 
  unsigned int index = ((*(cData->countCallsPtr)) % 8);
  
  // Transform raw temperature data to corrected temperature data
  (cData->tempCorrectedBufPtr[index]) = (unsigned char)( 5 + (0.75 * (cData->temperatureRawBufPtr[index])));
  //printf("tempCorrected: %i \n", cData->tempCorrectedBufPtr[index]);
  
  // Transform raw sys blood pressure data to corrected sys blood pressure data
  (cData->bloodPressCorrectedBufPtr[index]) = (unsigned char)(9 + (2 * (cData->bloodPressRawBufPtr[index])));
  //printf("sysCorrected: %i \n", cData->bloodPressCorrectedBufPtr[index]);
  
  // Transform raw dia blood pressure data to corrected dia blood pressure data
  (cData->bloodPressCorrectedBufPtr[index + 8]) = (unsigned char)(6 + (1.5 * (cData->bloodPressRawBufPtr[index + 8])));
  //printf("diaCorrected: %i \n", cData->bloodPressCorrectedBufPtr[index + 8]);
  
  // Transform raw pulse rate data to corrected pulse rate data
  //(cData->pulseRateCorrectedBufPtr[index + 8]) = (unsigned char)(8 + (3 * (cData->pulseRateRawBufPtr[index + 8])));
  //printf("PulseCorrected: %i \n", cData->pulseRateCorrectedBufPtr[index + 8]);
  }
  return;
}
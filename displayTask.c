#include "displayTask.h"
#include "dataStructs.c"
#include "dataPtrs.c"
#include "delays.h"
#include "drivers/rit128x96x4.h"
#include "systemTimeBase.h"

void disp(void* data)
{  

    //printf("\n CHECKING DISPLAY! \n");
    displayData2 * dData = (displayData2*)data;
    
    //find the current index of the array based on call count. 
    unsigned int index = ((*(dData->countCallsPtr)) % 8);
    unsigned int diaIndex = index + 8;
    
    //find the latest value of temperature
    unsigned char tempCorrect =(dData->tempCorrectedBufPtr[index]);
    
    char temp[20];
    sprintf(temp,"Temp %d C",tempCorrect);
    
    //find the latest value of systolic bp
    unsigned char sysCorrect =(dData->bloodPressCorrectedBufPtr[index]);
        
    //find the latest value of diastolic bp
    unsigned char diaCorrect =(dData->bloodPressCorrectedBufPtr[diaIndex]);
    
    char bP[35];
    sprintf(bP,"Sys/Dia %d/%d mmHg",sysCorrect,diaCorrect);
    
    
    //find the latest value of pulse rate
    unsigned char pulseCorrect =(dData->pulseRateCorrectedBufPtr[index]);
    
    char pulse[20];
    sprintf(pulse,"PR %d BPM",pulseCorrect);
    
    unsigned short battery = (*(dData->batteryStatePtr));
    
    char batt[20];
    sprintf(batt,"Batt %d ",battery);
    
    // Initialize the OLED display.
    RIT128x96x4Init(1000000);
    
    // Clear the OLED display
    //RIT128x96x4Clear();
    
    RIT128x96x4StringDraw(temp,5,9,15);
    RIT128x96x4StringDraw(bP,5,20,15);
    RIT128x96x4StringDraw(pulse,5,30,15);
    RIT128x96x4StringDraw(batt,80,9,15);
    
  
    return;
}
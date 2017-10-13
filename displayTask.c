#include "displayTask.h"
#include "dataStructs.c"
#include "dataPtrs.c"
#include "delays.h"
#include "drivers/rit128x96x4.h"

void disp(void* data)
{  
    displayData*word=(displayData*)data;
    unsigned char** temp1 = (*word).tempCorrectedPtr;
    unsigned char* temp2 =(unsigned char*)temp1;
    unsigned char number =*temp2;
    
    char temp[20];
    sprintf(temp,"Temp        %d C",number);
    
    temp1=(*word).sysCorrectedPtr;
    temp2=(unsigned char*)temp1;
    number =*temp2;
    
    char sys[20];
    sprintf(sys,"Systolic  %d mmHg",number);
    
    temp1=(*word).diasCorrectedPtr;
    temp2=(unsigned char*)temp1;
    number =*temp2;
    
    char dias[20];
    sprintf(dias,"Diastolic %d mmHg",number);
    
    
    temp1=(*word).prCorrectedPtr;
    temp2=(unsigned char*)temp1;
    number =*temp2;
    
    char pulse[20];
    sprintf(pulse,"Pulse Rate  %d BPM",number);
    
      
    unsigned short*temp3=(unsigned short*)(*word).batteryStatePtr;
    //number=(unsigned char*)temp1;
    number =*temp3;
    
    char batt[20];
    sprintf(batt,"Batt Stat   %d ",number);
    
    // Initialize the OLED display.
    RIT128x96x4Init(1000000);
    
    // Clear the OLED display
    RIT128x96x4Clear();
    
    RIT128x96x4StringDraw(temp,5,9,15);
    RIT128x96x4StringDraw(sys,5,20,15);
    RIT128x96x4StringDraw(dias,5,30,15);
    RIT128x96x4StringDraw(pulse,5,40,15);
    RIT128x96x4StringDraw(batt,5,50,15);
    
    delay(1000);
  
    return;
}
#include "displayTask.h"
#include "dataStructs.c"
#include "dataPtrs.c"
#include "delays.h"
#include "drivers/rit128x96x4.h"
#include "systemTimeBase.h"

void disp(void* data)
{  
  if(globalCounter % 50 < 5)
  {
    displayData*word=(displayData*)data;
    unsigned char** temp1 = (*word).tempCorrectedPtr;
    unsigned char* temp2 =(unsigned char*)temp1;
    unsigned char number =*temp2;
    
    char temp[20];
    sprintf(temp,"Temp %d C",number);
    
    temp1=(*word).sysCorrectedPtr;
    temp2=(unsigned char*)temp1;
    number =*temp2;
        
    temp1=(*word).diasCorrectedPtr;
    temp2=(unsigned char*)temp1;
    unsigned char number2 =*temp2;
    
    char bP[35];
    sprintf(bP,"Sys/Dia %d/%d mmHg",number,number2);
    
    
    temp1=(*word).prCorrectedPtr;
    temp2=(unsigned char*)temp1;
    number =*temp2;
    
    char pulse[20];
    sprintf(pulse,"PR %d BPM",number);
    
      
    unsigned short*temp3=(unsigned short*)(*word).batteryStatePtr;
    number =*temp3;
    
    char batt[20];
    sprintf(batt,"Batt %d ",number);
    
    // Initialize the OLED display.
    RIT128x96x4Init(1000000);
    
    // Clear the OLED display
    RIT128x96x4Clear();
    
    RIT128x96x4StringDraw(temp,5,9,15);
    RIT128x96x4StringDraw(bP,5,20,15);
    RIT128x96x4StringDraw(pulse,5,30,15);
    RIT128x96x4StringDraw(batt,80,9,15);
    
    delay(1000);
  }
  
    return;
}

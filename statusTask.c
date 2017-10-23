#include "statusTask.h"
#include "dataStructs.c"
#include "dataPtrs.c"
#include "systemTimeBase.h"

 void stat(void *data) {


     //printf("\n CHECKING STATUS! \n");
    // Recast task argument pointer to task’s data structure type
    statusData*word=(statusData*)data;
    unsigned short*temp3=(unsigned short*)(*word).batteryStatePtr;
   
    --*temp3;//= *temp3 - 1;
    //(*word).batteryStatePtr = (unsigned char *)(*temp3);
	return;

 }
	
 
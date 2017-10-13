#include "dataPtrs.c"
#include "dataStructs.c"

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
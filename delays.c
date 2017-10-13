
 
#include "drivers/rit128x96x4.h"
 
#include "delays.h"


/*
The function delay creates a delay.
Input:		A value of time to delay
Output: 	None
Function:  	The following routine creates a delay while executing the code.
*/

void delay(unsigned long aValue)
{
    //initialize variables
    volatile unsigned int i = 0;
    volatile unsigned int j = 0;
    
    //run loop
    for (i = aValue; i > 0; i--)
    {
        for (j = 0; j < aValue; j++);
    }
    
    return;
}

#include "drivers/rit128x96x4.h"

#include <stdio.h>

#include <string.h>

#include "inc/hw_types.h"

#include "driverlib/sysctl.h"

#include "driverlib/systick.h"

#include "inc/lm3s8962.h"

#include "systemTimeBase.h"

#include "inc/hw_ints.h"

#include "inc/hw_memmap.h"

#include "driverlib/debug.h"

#include "driverlib/gpio.h"

#include "driverlib/interrupt.h"

#include "driverlib/timer.h"

#include "buttontest.h"



#define CLOCK_RATE              300



//*****************************************************************************

//

// A set of flags used to track the state of the application.

//

//*****************************************************************************

extern unsigned long g_ulFlags;

#define FLAG_CLOCK_TICK         0           // A timer interrupt has occurred

#define FLAG_CLOCK_COUNT_LOW    1           // The low bit of the clock count

#define FLAG_CLOCK_COUNT_HIGH   2           // The high bit of the clock count

#define FLAG_UPDATE             3           // The display should be updated

#define FLAG_BUTTON             4           // Debounced state of the button

#define FLAG_DEBOUNCE_LOW       5           // Low bit of the debounce clock

#define FLAG_DEBOUNCE_HIGH      6           // High bit of the debounce clock

#define FLAG_BUTTON_PRESS       7           // The button was just pressed

#define FLAG_ENET_RXPKT         8           // An Ethernet Packet received

#define FLAG_ENET_TXPKT         9           // An Ethernet Packet transmitted

//*****************************************************************************

//

// The speed of the processor.

//

//*****************************************************************************

unsigned long g_ulSystemClock;



//*****************************************************************************

//

// The debounced state of the five push buttons.  The bit positions correspond

// to:

//

//     0 - Up

//     1 - Down

//     2 - Left

//     3 - Right

//     4 - Select

//

//*****************************************************************************

unsigned char g_ucSwitches = 0x1f;



//*****************************************************************************

//

// The vertical counter used to debounce the push buttons.  The bit positions

// are the same as g_ucSwitches.

//

//*****************************************************************************

static unsigned char g_ucSwitchClockA = 0;

static unsigned char g_ucSwitchClockB = 0;



//*****************************************************************************

//

// Handles the SysTick timeout interrupt.

//

//*****************************************************************************

void

SysTickIntHandler(void)

{

    unsigned long ulData, ulDelta;



    // Indicate that a timer interrupt has occurred.

    HWREGBITW(&g_ulFlags, FLAG_CLOCK_TICK) = 1;



    // Read the state of the push buttons.

    ulData = (GPIOPinRead(GPIO_PORTE_BASE, (GPIO_PIN_0 | GPIO_PIN_1 |

                                            GPIO_PIN_2 | GPIO_PIN_3)) |

              (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_1) << 3));



    // Determine the switches that are at a different state than the debounced state.

    //debug line to imitate up click

    //ulData = 30;

    ulDelta = ulData ^ g_ucSwitches;



    // Increment the clocks by one.

    // Exclusive or of clock B If a bit is different in A and B then 1 if the bits have the same value = 0

    g_ucSwitchClockA ^= g_ucSwitchClockB;

    // Compliment of clock B. This changes 1 to 0 and 0 to 1 bitwise

    g_ucSwitchClockB = ~g_ucSwitchClockB;



    // Reset the clocks corresponding to switches that have not changed state.

    g_ucSwitchClockA &= ulDelta;

    g_ucSwitchClockB &= ulDelta;



    // Get the new debounced switch state.

    g_ucSwitches &= g_ucSwitchClockA | g_ucSwitchClockB;

    g_ucSwitches |= (~(g_ucSwitchClockA | g_ucSwitchClockB)) & ulData;



    // Determine the switches that just changed debounced state.

    ulDelta ^= (g_ucSwitchClockA | g_ucSwitchClockB);



    // See if any switches just changed debounced state.

    if(ulDelta)

    {

        // You can watch the variable for ulDelta

        // Up = 1 Right = 8 down =2 left =4  select = 16 Bit values

        // Add the current tick count to the entropy pool.

        printf("A button was pressed %d \n", ulDelta);

    }



    // See if the select button was just pressed.

    if((ulDelta & 0x10) && !(g_ucSwitches & 0x10))

    {

        // Set a flag to indicate that the select button was just pressed.

        HWREGBITW(&g_ulFlags, FLAG_BUTTON_PRESS) = 1;

    }

}



void buttonTest(){

    // Set the clocking to use directly from crystal

    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |

                   SYSCTL_XTAL_8MHZ);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_8);



    // Get the system clock speed.

    g_ulSystemClock = SysCtlClockGet();



    // Enable the peripherals used by the application.

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);



    //

    // Configure the GPIOs used to read the state of the on-board push buttons.

    //

    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE,

                         GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    GPIOPadConfigSet(GPIO_PORTE_BASE,

                     GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,

                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_1);

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_STRENGTH_2MA,

                     GPIO_PIN_TYPE_STD_WPU);

    

    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);





    //

    // Configure SysTick to periodically interrupt.

    //

    SysTickPeriodSet(g_ulSystemClock / CLOCK_RATE);

    SysTickIntEnable();

    SysTickEnable();







    //

    // Throw away any button presses that may have occurred while the splash

    // screens were being displayed.

    //

    HWREGBITW(&g_ulFlags, FLAG_BUTTON_PRESS) = 0;



    //

    // Loop forever.

    //

    

};
#ifndef BUTTONTEST_H__
#define BUTTONTEST_H__

//*****************************************************************************
//
// The vertical counter used to debounce the push buttons.  The bit positions
// are the same as g_ucSwitches.
//
//*****************************************************************************
static unsigned char g_ucSwitchClockA;
static unsigned char g_ucSwitchClockB;

//*****************************************************************************
//
// Handles the SysTick timeout interrupt.
//
//*****************************************************************************
void SysTickIntHandler(void);
void buttonTest();

#endif
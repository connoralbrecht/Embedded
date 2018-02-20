#include "pushbutton.h"
#include "LED.h"
#include "timerA.h"


extern int p;
void InitializePushButtonPortPin (void)
{
    //input
    P1DIR &= ~BIT3;

    //enable pull up resistor
    P1REN |= BIT3;

    //set output as active low
    P1OUT |= BIT3;

    P1IE |= BIT3;
}

#pragma vector = PORT1_VECTOR

// Button interrupt service routine
__interrupt void Button_routine(void)
{
    p = 1 - p;
    P1IFG &= ~BIT3;
}

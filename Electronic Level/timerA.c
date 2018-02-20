#include "timerA.h"
//#include "LED.h"
#include "display.h"
#include "Accel.h"
#include "ADC.h"
#include "filter.h"
#include "cordic.h"

extern unsigned int g1msTimeout;
extern unsigned char calibrating;
extern LEDinfo info;
extern unsigned int CurrentSampleArray[3];
extern unsigned int XOut;
extern unsigned int YOut;
extern unsigned int ZOut;

void ConfigureTimerA(unsigned int top_val)
{
	// Timer0_A3 Control Register
    TA0CTL |= MC_0;     // Stop the timer
	TA0CTL |= TACLR;    // Clear the timer

	TA0CTL |= TASSEL_2 | ID_0 | MC_1;
	/* TASSEL1 = 0x0200 Timer A clock source select 0
	 * TASSEL0 = 0x0100 Timer A clock source select 1
	 *  00 = TACLK
	 *  01 = ACLK
	 *  10 = SMCLK
	 *  11 = INCLK
	 * ID1 = 0x0080 Timer A clock input divider 1
	 * ID0 = 0x0040 Timer A clock input divider 0
	 *  00 => Input divider = 1
	 *  01 => Input divider = 2
	 *  10 => Input divider = 4
	 *  11 => Input divider = 8
	 * MC1 = 0x0020 Timer A mode control 1
	 * MC0 = 0x0010 Timer A mode control 0
	 *  00 = Stop
	 *  01 = Up
	 *  10 = Continuous
	 *  11 = Up/Down
	 * TACLR = 0x0004 Timer A counter clear
	 * TAIE = 0x0002 Timer A counter interrupt enable
	 * TAIFG = 0x0001 Timer A counter interrupt flag
	 */

	TACCR0 = top_val;
	TA0CCR1 = top_val;

	// TACCR0 interrupt enabled (see Section 12.2.6 of User's Guide)
	TACCTL0 |= CCIE;
	TA0CCTL1 |= CCIE;
}

#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG0
__interrupt void TimerA0_routine(void)
{
    if(calibrating) {
        g1msTimeout++;
    }
    else {
        updateDisplay(&info);
        updateState(&info);
        updateMag(&info);
	}
}

#pragma vector = TIMER0_A1_VECTOR
// Interrupt service routine for CCIFG1 and TAIFG
    __interrupt void Timer0_A1_routine(void)
{
    switch (TAIV){
    case TA0IV_NONE:
        break;
    case TA0IV_TACCR1: // CCIFG1 interrupt
        // Start conversion
        ADC10CTL0 |= ADC10SC;

        ADC10SA = (unsigned int) CurrentSampleArray;
        // Wait for ADC conversion to complete.
        while (ADC10CTL1 & ADC10BUSY);

        // Read the current sample value from the ADC.
        //CurrentSample = ADC10MEM;


        filter();


        break;
    case TA0IV_TAIFG: // TAIFG interrupt
        break;
    default: for (;;); // Should not be possible
    }
}

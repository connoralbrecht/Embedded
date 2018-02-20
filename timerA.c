#include "timerA.h"
#include "LED.h"
#include "pushbutton.h"
extern int x;
extern int p;
void ConfigureTimerA(void)
{
    TA0CTL = (MC_0 | TACLR);

    //choose SMCLK, select an input divider, and start in mode
    TA0CTL = (TASSEL_2 | ID_3 | MC_1);

    //set value of CCR0
    TA0CCR0 = 499;

    //set value of CCR1
    TA0CCR1 = 1;

    //timer A interrupt enable
    TA0CTL |= TAIE;

    //compare/control 0 interrupt enable
    TA0CCTL0 |= CCIE;

    //compare/control 1 interrupt enable
    TA0CCTL1 |= CCIE;
}

#pragma vector = TIMER0_A0_VECTOR
// Interrupt service routine for CCIFG0
    __interrupt void Timer0_A0_routine(void)
{

        static char up;
        if(TA0CCR1 == TA0CCR0){
            x = -1;
            up = 0;
        }
        else if (TA0CCR1 > 0 && up == 0){
            x = -1;
        }
        else if(TA0CCR1 < TA0CCR0){
            x = 1;
            up = 1;
        }

        if(p == 0){
        TA0CCR1 += x;
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
        TURN_OFF_LED1;
        //P1OUT &= ~BIT1;
        break;
    case TA0IV_TAIFG: // TAIFG interrupt
        //cancel out flash
        if(TA0CCR1 > 10){
        TURN_ON_LED1;
        }
        //P1OUT |= BIT1;
        break;
    default: for (;;); // Should not be possible
    }
}

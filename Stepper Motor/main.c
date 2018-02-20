#include <msp430.h> 

#include "timerA.h"
#include "step.h"

// Function Prototypes
void ConfigureClockModule();
void ManageSoftwareTimers(void);

// Global variables
unsigned int g1msTimeout = 0;
unsigned int g1msTimer = 0;
int output;
unsigned char ones;
unsigned char tens;
int lastCount;

// out2a and out2b



void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;


    ConfigureClockModule();
    ConfigureStep();
    ConfigureTimerA();



    _enable_interrupts();

    while(1){

    }

}

void ConfigureClockModule()
{
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations
    DCOCTL  = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
}

void ManageSoftwareTimers(void)
{
    if (g1msTimeout) {
        g1msTimeout--;
        g1msTimer++;
    }
}


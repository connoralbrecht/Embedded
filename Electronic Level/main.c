#include <msp430.h> 
#include <math.h>
#include "spi.h"
#include "display.h"
#include "timerA.h"
#include "pushbutton.h"
#include "debounce.h"
#include "Accel.h"
#include "ADC.h"
#include "filter.h"
#include "cordic.h"

#define TEST_SIZE 5




// Local prototypes
void ConfigureClockModule();
void InitializeSampleBuffer(void);



// Global Variables
unsigned int g1msTimeout;       // This variable is incremented by the interrupt handler and
                                // decremented by a software call in the main loop.
unsigned int g1msTimer;         // This variable is incremented in ManageSoftwareTimers
LEDinfo info;
unsigned char calibrating = 1;
unsigned int XOut;
unsigned int YOut;
unsigned int ZOut;
unsigned int XMid;
unsigned int YMid;
unsigned int ZMid;
unsigned int XMax;
unsigned int XMin;
unsigned int YMax;
unsigned int YMin;
unsigned int ZMax;
unsigned int ZMin;
unsigned int XMid;
unsigned int YMid;
unsigned int ZMid;
unsigned int X0;
unsigned int Y0;
unsigned int Z0;
unsigned int n;
unsigned int x[NUMBER_OF_SAMPLES];
unsigned int y[NUMBER_OF_SAMPLES];
unsigned int z[NUMBER_OF_SAMPLES];
unsigned int CurrentSampleArray[3];

extern const long cordic_ctab_degrees[CORDIC_NTAB];

void normalize();

int main(void)
{


	WDTCTL = WDTPW | WDTHOLD;
	ConfigureClockModule();
	
	InitializeSPI();
	InitializeDisplay();
	ConfigureTimerA(TA0CCR0_VALUE);
	InitializePushButtonPortPin();
	ConfigureADC();
    InitializeAccel();
    InitializeSampleBuffer();

	InitializeLEDStatus(&info);

	_enable_interrupts();

	calibrate();

	ConfigureTimerA(6999);

	calibrating = 0;
	normalize();
	while(1) {
	    tilt(XOut, YOut, ZOut);
	}
}

void ConfigureClockModule()
{
    // Configure Digitally Controlled Oscillator (DCO) using factory calibrations
    DCOCTL  = CALDCO_16MHZ;
    BCSCTL1 = CALBC1_16MHZ;
}

void InitializeSampleBuffer(void)
{
    unsigned char i;

    for (i = 0; i < NUMBER_OF_SAMPLES; i++) x[i] = 0;

    CurrentSampleArray[0] = 0;
    CurrentSampleArray[1] = 0;
    CurrentSampleArray[2] = 0;

    n = 0;

    XOut = 0;
    YOut = 0;
    ZOut = 0;

}
void normalize(){
    XMid = (XMax + XMin) >> 1;
    YMid = (YMax + YMin) >> 1;
    ZMid = (ZMax + ZMin) >> 1;
    X0 = XMid;
    Y0 = YMid;
    Z0 = ZMid;

}



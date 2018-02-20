#ifndef TIMER_A_H
#define TIMER_A_H

#include <msp430.h>
#include "spi.h"
#include "DAC.h"

#define TACCR0_VALUE (1563-1)   // 12 MHz MCLK divided by Fs=7680 Hz (128 sample points * 60 Hz)
#define SCALING_FACTOR 6    // Scale 10-bit ADC values for 16-bit DAC.

// Function Prototypes
void ConfigureTimerA0(void);

#endif

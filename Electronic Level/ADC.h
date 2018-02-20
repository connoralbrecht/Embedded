#ifndef ADC_H
#define ADC_H

#include <msp430.h>

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *      ADC10 Analog Input
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *   GPIO      :  P1.0
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#define ADC10_ANALOG_INPUT_BIT_X        BIT0
#define ADC10_ANALOG_INPUT_X            INCH_0

#define ADC10_ANALOG_INPUT_BIT_Y        BIT1
#define ADC10_ANALOG_INPUT_Y            INCH_1

#define ADC10_ANALOG_INPUT_BIT_Z        BIT2
#define ADC10_ANALOG_INPUT_Z            INCH_2

// Prototypes
void ConfigureADC(void);

#endif

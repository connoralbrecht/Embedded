#include "ADC.h"

void ConfigureADC(void)
{
    /* ADC10 Control register 0
     * SREF_0: Choose supply voltages as reference.
     * ADC10SHT_2: sample + hold @ 16 ADC10CLKs
     * ADC10ON: Turn on ADC.
     */
    ADC10CTL0 = (SREF_0 + ADC10SHT_2 + ADC10ON + MSC);

    // ADC10 Control register 1
    // ADC10OSC as ADC10CLK; Single-channel-single-conversion
    ADC10CTL1 = ADC10_ANALOG_INPUT_Z + ADC10SSEL_0 + CONSEQ_1;

    // Enable the analog inputs.
    ADC10AE0 = ADC10_ANALOG_INPUT_BIT_X + ADC10_ANALOG_INPUT_BIT_Y + ADC10_ANALOG_INPUT_BIT_Z;

    ADC10DTC1 = 0x03;
    __delay_cycles(128);            // Delay to allow Ref to settle

    ADC10CTL0 |=  (ENC | ADC10SC); // Enable and start conversion
}

#include "filter.h"

extern int y;
extern int x[NUMBER_OF_SAMPLES];
extern unsigned int n;
extern unsigned int CurrentSample;
unsigned int CumSum = 0;

void filter()
{
    CumSum -= x[n];
    // Update the sample array, x.
    x[n] = CurrentSample;


    // Generate the filter output.
    CumSum += x[n];
    y = CumSum >> 7;
    n = (n+1) & 127;

}

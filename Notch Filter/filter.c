#include "filter.h"

extern int y;
extern int x[NUMBER_OF_SAMPLES];
extern unsigned int n;
extern unsigned int CurrentSample;
unsigned int n_d;

void filter()
{
    // Update the sample array, x.
    x[n] = CurrentSample;


    // Generate the filter output.
    n_d = (n-32) & 63;
    n = (n+1) & 63;

    y = ((CurrentSample + x[n_d]) >> 1);


}

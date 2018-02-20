#include "filter.h"

extern int XOut;
extern int YOut;
extern int ZOut;
extern int x[NUMBER_OF_SAMPLES];
extern int y[NUMBER_OF_SAMPLES];
extern int z[NUMBER_OF_SAMPLES];
extern unsigned int n;
unsigned int CumSumX = 0;
unsigned int CumSumY = 0;
unsigned int CumSumZ = 0;
extern unsigned int CurrentSampleArray[3];

void filter()
{
    CumSumX -= x[n];
    CumSumY -= y[n];
    CumSumZ -= z[n];
    // Update the sample array, x.
    x[n] = CurrentSampleArray[2];
    y[n] = CurrentSampleArray[1];
    z[n] = CurrentSampleArray[0];


    // Generate the filter output.
    CumSumX += x[n];
    CumSumY += y[n];
    CumSumZ += z[n];

    XOut = CumSumX >> 3;
    YOut = CumSumY >> 3;
    ZOut = CumSumZ >> 3;
    n = (n+1) & 7;

}

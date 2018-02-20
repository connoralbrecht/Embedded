#include "cordic.h"
#include "display.h"

extern LEDinfo info;
extern int ZOut;
extern unsigned int XMid;
extern unsigned int YMid;
extern unsigned int ZMid;
extern unsigned int X0;
extern unsigned int Y0;
extern unsigned int Z0;
extern LEDinfo info;
long theta;
long phi;
long r;


const long cordic_ctab_degrees [CORDIC_NTAB] = { // Angle units = degrees
    0x00002D00, 0x00001A90, 0x00000E09, 0x00000720,
    0x00000393, 0x000001CA, 0x000000E5, 0x00000072,
    0x00000039, 0x0000001C, 0x0000000E, 0x00000007,
    0x00000003, 0x00000001, 0x00000000, 0x00000000 };

void Cordic(calculations *calcs, char return_type)
{
    int k, n = 16;
    long Xnew,Ynew,Anew,X,Y,A,cordic_ctab_value;
    
    // Initialize X, Y, and angle.
    X = calcs->x; Y = calcs->y; A = calcs->angle;
    
    for (k=0; k<n; ++k)
    {
        cordic_ctab_value = cordic_ctab_degrees[k];
        if (return_type == ATAN_HYP) {
            if (Y > 0) {
                Xnew = X + (Y>>k);
                Ynew = Y - (X>>k);
                Anew = A + cordic_ctab_value;
            }
            if (Y < 0) {
                Xnew = X - (Y>>k);
                Ynew = Y + (X>>k);
                Anew = A - cordic_ctab_value;                
            }
        }
        else {
            if (A > 0) {
                Xnew = X - (Y>>k);
                Ynew = Y + (X>>k);
                Anew = A - cordic_ctab_value;
            }
            if (A < 0) {
                Xnew = X + (Y>>k);
                Ynew = Y - (X>>k);
                Anew = A + cordic_ctab_value;
            }
        }
        X = Xnew; Y = Ynew; A = Anew;
    }
    calcs->x = X;
    calcs->y = Y;
    calcs->angle = A;
}

void tilt(long x, long y, long z)
{
//Different pins correspond to different x,y,z values
    //need to get angle to get sin/cos readings
    //use to determine if flat
    //Z determines quad
    //x and y to determine angle to pick
    calculations cords;
    volatile float angle, hypotenuse;
    x -= X0;
    y -= Y0;
    z -= Z0;


           if (x >= 0) { // first quadrant and fourth quadrant
               cords.x = MUL*x; cords.y = MUL*y; cords.angle = 0;
               Cordic((calculations *)&cords,ATAN_HYP);
               angle = ((float) cords.angle)/MUL;
           }
           else if (x < 0 && y >= 0) { // second quadrant
               cords.x = -1.0*MUL*x; cords.y = MUL*y; cords.angle = 0;
               Cordic((calculations *)&cords,ATAN_HYP);
               angle = 180.0 - ((float) cords.angle)/MUL;
           }
           else if (x < 0 && y < 0) { // third quadrant
               cords.x = -1.0*MUL*x; cords.y = -1.0*MUL*y; cords.angle = 0;
               Cordic((calculations *)&cords,ATAN_HYP);
               angle = ((float) cords.angle)/MUL - 180.0;
           }

           // X is adjusted by the CORDIC_GAIN, which equals 0x9B (155 decimal), for
           // MUL = 256 and CORDIC_GAIN = 0.607252935103139.  However, if X = Y,
           // then the CORDIC_GAIN = sqrt(2)/2.
           if (x == y) {
               hypotenuse = ((float) cords.x)*CORDIC_GAIN_X_EQUALS_Y/MUL;
           }
           else {
               hypotenuse = ((float) cords.x)*CORDIC_GAIN/MUL;
           }
           _nop();

    theta = angle;
    r = hypotenuse;


                if (r >= 0) { // first quadrant and fourth quadrant
                   cords.x = MUL*r; cords.y = MUL*z; cords.angle = 0;
                   Cordic((calculations *)&cords,ATAN_HYP);
                   angle = ((float) cords.angle)/MUL;
               }
               else if (r < 0 && z >= 0) { // second quadrant
                   cords.x = -1.0*MUL*r; cords.y = MUL*z; cords.angle = 0;
                   Cordic((calculations *)&cords,ATAN_HYP);
                   angle = 180.0 - ((float) cords.angle)/MUL;
               }
               else if (r < 0 && z < 0) { // third quadrant
                   cords.x = -1.0*MUL*r; cords.y = -1.0*MUL*z; cords.angle = 0;
                   Cordic((calculations *)&cords,ATAN_HYP);
                   angle = ((float) cords.angle)/MUL - 180.0;
               }

       phi = angle;
       if(phi < 0){
           phi = (-1)*phi;
       }
       if(phi < 80 || phi > 110){
           if(theta >= -22.5 && theta <= 22.5){
               info.state = north;
           }
           else if(theta < -22.5 && theta > -67.5){
               info.state = northeast;
           }
           else if(theta <= -67.5 && theta >= -112.5){
               info.state = east;
           }
           else if(theta > -157.5 && theta < -112.5){
               info.state = southeast;
           }
           else if(theta >= 157.5 || theta <= -157.5){
               info.state = south;
           }
           else if(theta > 112.5 && theta < 157.5){
               info.state = southwest;
           }
           else if(theta >= 67.5 && theta <= 112.5){
               info.state = west;
           }
           else if(theta > 22.5 && theta < 67.5){
               info.state = northwest;
           }
       }
       else{
           info.state = flat;
           info.mag = high;
       }

       if(phi > 54 && phi < 80){
           info.mag = low;
       }
       else if(phi < 27){
           info.mag = high;
       }
       else{
           info.mag = medium;
       }


}


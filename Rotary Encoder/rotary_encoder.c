#include "rotary_encoder.h"

void InitializeRotaryEncoderPortPins(void)
{
    SET_ROTARY_ENCODER_A_AS_AN_INPUT;
    SET_ROTARY_ENCODER_B_AS_AN_INPUT;
}

EncoderState RotaryEncoder(EncoderDefinitions *myRotorEncoder, EncoderState *myEncoderState)
{
    EncoderState NextEncoderState;

    switch (*myEncoderState) {


    case Initialize:
        if(myRotorEncoder->Reset == High){
                   myRotorEncoder->RotaryEncoderStateCount = 0;
                   NextEncoderState = Initialize;
          }
        else if(myRotorEncoder->SwitchA == High && myRotorEncoder->SwitchB == High){

               NextEncoderState = AhighBhigh;
        }
        else if(myRotorEncoder->SwitchA == Low && myRotorEncoder->SwitchB == High){

               NextEncoderState = AlowBhigh;
        }
        else if(myRotorEncoder->SwitchA == Low && myRotorEncoder->SwitchB == Low){

               NextEncoderState = AlowBlow;
        }
        else{
               NextEncoderState = AhighBlow;
        }
        break;

    case AlowBlow:
        if(myRotorEncoder->Reset == High){
                   myRotorEncoder->RotaryEncoderStateCount = 0;
                   NextEncoderState = Initialize;
            }
        else if(myRotorEncoder->SwitchA == High && myRotorEncoder->SwitchB == Low){
                myRotorEncoder->RotaryEncoderStateCount++;
                NextEncoderState = AhighBlow;
        }
        else if(myRotorEncoder->SwitchA == Low && myRotorEncoder->SwitchB == High){
            myRotorEncoder->RotaryEncoderStateCount--;
               NextEncoderState = AlowBhigh;
        }
        else{
               NextEncoderState = AlowBlow;
        }
        break;

    case AlowBhigh:
        if(myRotorEncoder->Reset == High){
                   myRotorEncoder->RotaryEncoderStateCount = 0;
                   NextEncoderState = Initialize;
            }
        else if(myRotorEncoder->SwitchA == High && myRotorEncoder->SwitchB == High){
                myRotorEncoder->RotaryEncoderStateCount--;
                NextEncoderState = AhighBhigh;
        }
        else if(myRotorEncoder->SwitchA == Low && myRotorEncoder->SwitchB == Low){
                myRotorEncoder->RotaryEncoderStateCount++;
                NextEncoderState = AlowBlow;
        }
        else{
                NextEncoderState = AlowBhigh;
        }
        break;

    case AhighBlow:
        if(myRotorEncoder->Reset == High){
                   myRotorEncoder->RotaryEncoderStateCount = 0;
                   NextEncoderState = Initialize;
            }
        else if(myRotorEncoder->SwitchA == High && myRotorEncoder->SwitchB == High){
                myRotorEncoder->RotaryEncoderStateCount++;
                NextEncoderState = AhighBhigh;
        }
        else if(myRotorEncoder->SwitchA == Low && myRotorEncoder->SwitchB == Low){
                myRotorEncoder->RotaryEncoderStateCount--;
                NextEncoderState = AlowBlow;
        }
        else{
                NextEncoderState = AhighBlow;
        }
        break;

    case AhighBhigh:
        if(myRotorEncoder->Reset == High){
                   myRotorEncoder->RotaryEncoderStateCount = 0;
                   NextEncoderState = Initialize;
            }
        else if(myRotorEncoder->SwitchA == High && myRotorEncoder->SwitchB == Low){
                myRotorEncoder->RotaryEncoderStateCount--;
                NextEncoderState = AhighBlow;
        }
        else if(myRotorEncoder->SwitchA == Low && myRotorEncoder->SwitchB == High){
            myRotorEncoder->RotaryEncoderStateCount++;
               NextEncoderState = AlowBhigh;
        }
        else{
               NextEncoderState = AhighBhigh;
        }
        break;

    default:
        NextEncoderState = Initialize;
        break;
    }



    return NextEncoderState;
}

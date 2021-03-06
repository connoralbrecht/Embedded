#include <msp430.h> 

#include "pushbutton.h"
#include "debounce.h"
#include "timerA.h"
#include "rotary_encoder.h"
#include "spi.h"
#include "LED_display.h"

// Function Prototypes
void ConfigureClockModule();
void ManageSoftwareTimers(void);

// Global variables
unsigned int g1msTimeout = 0;
unsigned int g1msTimer = 0;
unsigned int DisplayValue = 0;

void main(void)
{
    InitializeSPI();
    InitializeLEDDisplay();
   // SetLEDDisplay(DisplayValue);
    SwitchDefine gRotaryEncoderReset; // Used to reset the timer and LED display.
    SwitchDefine gRotaryEncoderA;
    SwitchDefine gRotaryEncoderB;

    EncoderDefinitions myRotaryEncoder;
    EncoderState myEncoderState = Initialize; // Current state of the rotary encoder

    WDTCTL = WDTPW | WDTHOLD;       // Stop watchdog timer
    ConfigureClockModule();

    // Initialize hardware.
    InitializePushButtonPortPin();
    ConfigureTimerA();
    InitializeRotaryEncoderPortPins();

    // Initialize the input "switches" to the rotary encoder.
    InitializeSwitch(&gRotaryEncoderReset,(char *) &PUSHBUTTON_PORT_IN,(unsigned char) PUSHBUTTON_BIT,
            HIGH_THRESHOLD,LOW_THRESHOLD);
    InitializeSwitch(&gRotaryEncoderA,(char *) &ROTARY_ENCODER_A_PORT,(unsigned char) ROTARY_ENCODER_A_BIT,
            ROTARY_ENCODER_BOUNCE_TIME_MAX,ROTARY_ENCODER_BOUNCE_TIME_MAX);
    InitializeSwitch(&gRotaryEncoderB,(char *) &ROTARY_ENCODER_B_PORT,(unsigned char) ROTARY_ENCODER_B_BIT,
            ROTARY_ENCODER_BOUNCE_TIME_MAX,ROTARY_ENCODER_BOUNCE_TIME_MAX);

    _enable_interrupts();

    while (1) {

        // First, update software timers.
        ManageSoftwareTimers();

        // Then, determine the debounced inputs to rotary encoder state machine.
        myRotaryEncoder.Reset = Debouncer(&gRotaryEncoderReset);
        myRotaryEncoder.SwitchA = Debouncer(&gRotaryEncoderA);
        myRotaryEncoder.SwitchB = Debouncer(&gRotaryEncoderB);

        // Next, use the debounced inputs and the current state to generate the next state.
        myEncoderState = RotaryEncoder(&myRotaryEncoder,&myEncoderState);

        // Now, perform the appropriate output task(s).
        if (myEncoderState == Initialize) {
            DisplayValue = 0;
            SetLEDDisplay(DisplayValue);
            // Code for when the button is pushed to reset the timer/LED display.
           // _nop();
        }
        else {
            if(myRotaryEncoder.RotaryEncoderStateCount == 4){
                if(DisplayValue <99){
                DisplayValue++;
                }
                myRotaryEncoder.RotaryEncoderStateCount = 0;
            }
            else if(myRotaryEncoder.RotaryEncoderStateCount == -4){
                if(DisplayValue > 0){
                DisplayValue--;
                }
                myRotaryEncoder.RotaryEncoderStateCount = 0;
            }
            if(g1msTimer >= 1000){
                if(DisplayValue >= 1){
                    DisplayValue--;
                }
                g1msTimer = 0;
            }
            SetLEDDisplay(DisplayValue);
            // Code for when rotary encoder is being rotated to set the timer,
            // or the timer is counting down.
           // _nop();
        }
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

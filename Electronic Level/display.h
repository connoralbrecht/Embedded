#ifndef DISPLAY_H
#define DISPLAY_H

#include <msp430.h>

//LED states
typedef enum LEDStates {
    north, northwest, west, southwest, south, southeast, east, northeast, flat
} LEDState;

//LED brightness
typedef enum LEDMag {
    low, medium, high
} LEDMag;

typedef struct LEDStruct {
    char LEDStatus;
    char mid;
    char first;
    char all;
    int Period;
    int curTime;
    int Onticks[3];
    LEDState state;
    LEDMag mag;
} LEDinfo;



//Latch, pin 2.0
#define LATCH_BIT                BIT0
#define LATCH_PORT               P2OUT
#define LATCH_DDR                P2DIR
#define SET_LATCH_AS_AN_OUTPUT   LATCH_DDR |= LATCH_BIT
#define TURN_ON_LATCH            LATCH_PORT |= LATCH_BIT
#define TURN_OFF_LATCH           LATCH_PORT &= ~LATCH_BIT
#define TOGGLE_LATCH             LATCH_PORT ^= LATCH_BIT

//Blank, pin 1.4
#define BLANK_BIT                BIT4
#define BLANK_PORT               P1OUT
#define BLANK_DDR                P1DIR
#define SET_BLANK_AS_AN_OUTPUT   BLANK_DDR |= BLANK_BIT
#define TURN_ON_BLANK            BLANK_PORT |= BLANK_BIT
#define TURN_OFF_BLANK           BLANK_PORT &= ~BLANK_BIT
#define TOGGLE_BLANK             BLANK_PORT ^= BLANK_BIT


//directions
#define NORTH                   0x80
#define NORTH_FIRST             0xC1
#define NORTH_ALL               0xE3

#define NORTHWEST               0x01
#define NORTHWEST_FIRST         0x82
#define NORTHWEST_SECOND        0x44
#define NORTHWEST_ALL           0xC7

#define WEST                    0x02
#define WEST_FIRST              0x05
#define WEST_SECOND             0x88
#define WEST_ALL                0x8F

#define SOUTHWEST               0x04
#define SOUTHWEST_FIRST         0x0A
#define SOUTHWEST_SECOND        0x11
#define SOUTHWEST_ALL           0x1F

#define SOUTH                   0x08
#define SOUTH_FIRST             0x14
#define SOUTH_SECOND            0x22
#define SOUTH_ALL               0x3E

#define SOUTHEAST               0x10
#define SOUTHEAST_FIRST         0x28
#define SOUTHEAST_SECOND        0x44
#define SOUTHEAST_ALL           0x7C

#define EAST                    0x20
#define EAST_FIRST              0x50
#define EAST_SECOND             0x88
#define EAST_ALL                0xF8

#define NORTHEAST               0x40
#define NORTHEAST_FIRST         0xA0
#define NORTHEAST_SECOND        0x11
#define NORTHEAST_ALL           0xF1

#define FLAT                    0xFF

#define UP                      0xAA
#define DOWN                    0x55



//function prototypes
void InitializeDisplay();
void InitializeLEDStatus(LEDinfo *info);
void setDisplay(unsigned char value);
void updateDisplay(LEDinfo *info);
void resetOnticks(LEDinfo *info);
void updateState(LEDinfo *info);
void updateMag(LEDinfo *info);
void calibrate();
void ManageSoftwareTimers(void);

#endif

#include "display.h"
#include "spi.h"
#include "pushbutton.h"
#include "debounce.h"

int curTime = 0;
unsigned int top;
unsigned int mid;
unsigned int bot;
extern unsigned int XMax;
extern unsigned int XMin;
extern unsigned int YMax;
extern unsigned int YMin;
extern unsigned int ZMax;
extern unsigned int ZMin;
extern unsigned int XMid;
extern unsigned int YMid;
extern unsigned int ZMid;
extern unsigned int g1msTimeout;
extern unsigned int g1msTimer;
extern unsigned char calibrating;
extern unsigned int XOut;
extern unsigned int YOut;
extern unsigned int ZOut;


void InitializeDisplay() {
    TURN_OFF_LATCH;
    SET_LATCH_AS_AN_OUTPUT;
    TURN_OFF_BLANK;
    SET_BLANK_AS_AN_OUTPUT;
}

void setDisplay(unsigned char value) {
    SPISendByte(value);
    TOGGLE_LATCH;
    TOGGLE_LATCH;
}

void InitializeLEDStatus(LEDinfo *info) {
    info->Period = 50;
    info->state = north;
    info->curTime = 0;
    info->mid = NORTH;
    info->first = NORTH_FIRST;
    info->all = NORTH_ALL;
    info->mag = low;
}

void updateDisplay(LEDinfo *info) {
    if(curTime == info->Period) {
        setDisplay(info->all);
        curTime = 0;
        resetOnticks(info);
    }
    else {
        if(info->Onticks[0] < 0) {
            setDisplay(0x00);
        }
        else if(info->Onticks[1] < 0) {
            setDisplay(info->mid);
        }
        else if(info->Onticks[2] < 0) {
            setDisplay(info->first);
        }
        else {
            setDisplay(info->all);
        }
        info->Onticks[0]--;
        info->Onticks[1]--;
        info->Onticks[2]--;
    }
    curTime++;
}

void resetOnticks(LEDinfo *info) {
    info->Onticks[0] = top;
    info->Onticks[1] = mid;
    info->Onticks[2] = bot;
}

void updateState(LEDinfo *info) {
    switch(info->state) {
    case north:
        info->mid = NORTH;
        info->first = NORTH_FIRST;
        info->all = NORTH_ALL;
        break;
    case northwest:
        info->mid = NORTHWEST;
        info->first = NORTHWEST_FIRST;
        info->all = NORTHWEST_ALL;
        break;
    case west:
        info->mid = WEST;
        info->first = WEST_FIRST;
        info->all = WEST_ALL;
        break;
    case southwest:
        info->mid = SOUTHWEST;
        info->first = SOUTHWEST_FIRST;
        info->all = SOUTHWEST_ALL;
        break;
    case south:
        info->mid = SOUTH;
        info->first = SOUTH_FIRST;
        info->all = SOUTH_ALL;
        break;
    case southeast:
        info->mid = SOUTHEAST;
        info->first = SOUTHEAST_FIRST;
        info->all = SOUTHEAST_ALL;
        break;
    case east:
        info->mid = EAST;
        info->first = EAST_FIRST;
        info->all = EAST_ALL;
        break;
    case northeast:
        info->mid = NORTHEAST;
        info->first = NORTHEAST_FIRST;
        info->all = NORTHEAST_ALL;
        break;
    case flat:
        info->mid = FLAT;
        info->first = FLAT;
        info->all = FLAT;
        break;
    }
}

void updateMag(LEDinfo *info) {
    switch (info->mag) {
    case high:
        top = 49;
        mid = 28;
        bot = 10;
        break;
    case medium:
        top = 35;
        mid = 19;
        bot = 5;
        break;
    case low:
        top = 28;
        mid = 10;
        bot = 1;
        break;
    }
}

void calibrate() {
    unsigned char upPress = 0;
    unsigned char curCal = 0;
    volatile SwitchStatus PushButtonStatus;
    SwitchDefine PushButton;
    InitializeSwitch(&PushButton,(char *) &PUSHBUTTON_PORT_IN,(unsigned char) PUSHBUTTON_BIT,
        HIGH_THRESHOLD,LOW_THRESHOLD);
    while(calibrating) {
        ManageSoftwareTimers();
        PushButtonStatus = Debouncer(&PushButton);
        switch (curCal) {
        case 0:
            setDisplay(NORTH);
            if(!upPress) {
                if (PushButtonStatus == High) {
                    upPress = 1;
                    XMax = XOut;
                }
            }
            else {
                if (PushButtonStatus == Low) {
                    upPress = 0;
                    curCal = 1;
                }
            }
            break;
        case 1:
            setDisplay(SOUTH);
            if(!upPress) {
                if (PushButtonStatus == High) {
                    upPress = 1;
                    XMin = XOut;
                }
            }
            else {
                if (PushButtonStatus == Low) {
                    upPress = 0;
                    curCal = 2;
                }
            }
            break;
        case 2:
            setDisplay(EAST);
            if(!upPress) {
                if (PushButtonStatus == High) {
                    upPress = 1;
                    YMin = YOut;
                }
            }
            else {
                if (PushButtonStatus == Low) {
                    upPress = 0;
                    curCal = 3;
                }
            }
            break;
        case 3:
            setDisplay(WEST);
            if(!upPress) {
                if (PushButtonStatus == High) {
                    upPress = 1;
                    YMax = YOut;
                }
            }
            else {
                if (PushButtonStatus == Low) {
                    upPress = 0;
                    curCal = 4;
                }
            }
            break;
        case 4:
            setDisplay(UP);
            if(!upPress) {
                if (PushButtonStatus == High) {
                    upPress = 1;
                    ZMax = ZOut;
                }
            }
            else {
                if (PushButtonStatus == Low) {
                    upPress = 0;
                    curCal = 5;
                }
            }
            break;
        case 5:
            setDisplay(DOWN);
            if(!upPress) {
                if (PushButtonStatus == High) {
                    upPress = 1;
                    ZMin = ZOut;
                }
            }
            else {
                if (PushButtonStatus == Low) {
                    upPress = 0;
                    calibrating = 0;
                }
            }
            break;
        }
    }

    XMid = (XMax + XMin) >> 1;
    YMid = (YMax + YMin) >> 1;
    ZMid = (ZMax + ZMin) >> 1;


}

void ManageSoftwareTimers(void)
{
    if (g1msTimeout){
        g1msTimeout--;
        g1msTimer++;
    }
}

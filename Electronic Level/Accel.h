#ifndef ACCEL_H_
#define ACCEL_H_
#include <msp430.h>


#define X_BIT        BIT0
#define X_PORT       P1IN
#define X_DDR        P1DIR
#define X_AS_INPUT   X_DDR &= ~X_BIT
#define X_ENABLE     X_PORT |= X_BIT
#define X_DISABLE    X_PORT &= ~X_BIT

#define Y_BIT        BIT1
#define Y_PORT       P1IN
#define Y_DDR        P1DIR
#define Y_AS_INPUT   Y_DDR &= ~Y_BIT
#define Y_ENABLE     Y_PORT |= Y_BIT
#define Y_DISABLE    Y_PORT &= ~Y_BIT

#define Z_BIT        BIT2
#define Z_PORT       P1IN
#define Z_DDR        P1DIR
#define Z_AS_INPUT   Z_DDR &= ~Z_BIT
#define Z_ENABLE     Z_PORT |= Z_BIT
#define Z_DISABLE    Z_PORT &= ~Z_BIT

void InitializeAccel(void);

#endif

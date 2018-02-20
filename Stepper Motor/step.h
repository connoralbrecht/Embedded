/*
 * step.h
 *
 *  Created on: Nov 16, 2017
 *      Author: Kevin
 */

#ifndef STEP_H
#define STEP_H

#include <msp430.h>

//FLip ports and bits in enable/disable
#define STEP_BIT        BIT2
#define STEP_PORT       P2OUT
#define STEP_DDR        P2DIR
#define STEP_OUTPUT     STEP_DDR |= STEP_BIT
#define ENABLE_STEP     STEP_PORT |= STEP_BIT
#define DISABLE_STEP    STEP_PORT &= ~STEP_BIT
#define TOGGLE_STEP     STEP_PORT ^= STEP_BIT

#define MS1_BIT         BIT4
#define MS1_PORT        P2OUT
#define MS1_DDR         P2DIR
#define MS1_OUTPUT      MS1_DDR |= MS1_BIT
#define MS1_ENABLE      MS1_PORT |= MS1_BIT
#define MS1_DISABLE     MS1_PORT &= ~MS1_BIT

#define MS2_BIT         BIT7
#define MS2_PORT        P1OUT
#define MS2_DDR         P1DIR
#define MS2_OUTPUT      MS2_DDR |= MS2_BIT
#define MS2_ENABLE      MS2_PORT |= MS2_BIT
#define MS2_DISABLE     MS2_PORT &= ~MS2_BIT

#define RESET_BIT       BIT5
#define RESET_PORT      P2OUT
#define RESET_DDR       P2DIR
#define RESET_OUTPUT    RESET_DDR |= RESET_BIT
#define RESET_ENABLE    RESET_PORT &= ~RESET_BIT //active low
#define RESET_DISABLE   RESET_PORT |= RESET_BIT

#define SLEEP_BIT       BIT1
#define SLEEP_PORT      P2OUT
#define SLEEP_DDR       P2DIR
#define SLEEP_OUTPUT    SLEEP_DDR |= SLEEP_BIT
#define ENABLE_SLEEP    SLEEP_PORT &= ~SLEEP_BIT // active low
#define DISABLE_SLEEP   SLEEP_PORT |= SLEEP_BIT

#define DIR_BIT         BIT3
#define DIR_PORT        P2OUT
#define DIR_DDR         P2DIR
#define DIR_OUTPUT      DIR_DDR |= DIR_BIT
#define SET_DIR         DIR_PORT |= DIR_BIT

//active low enable
#define ENABLE_BIT      BIT6
#define ENABLE_PORT     P1OUT
#define ENABLE_DDR      P1DIR
#define ENABLE_OUTPUT   ENABLE_DDR |= ENABLE_BIT
#define ENABLE          ENABLE_PORT &= ~ENABLE_BIT //active low
#define DISABLE         ENABLE_PORT |= ENABLE_BIT

void ConfigureStep();

#endif /* STEP_H_ */

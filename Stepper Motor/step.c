/*
 * step.c
 *
 *  Created on: Nov 16, 2017
 *      Author: Kevin
 */

#include "step.h"

void ConfigureStep()
{

    ENABLE_OUTPUT;
    MS1_OUTPUT;
    MS2_OUTPUT;
    SLEEP_OUTPUT;
    STEP_OUTPUT;
    DIR_OUTPUT;
    RESET_OUTPUT;
    ENABLE;
    DISABLE_SLEEP;
    RESET_DISABLE;
    SET_DIR;
    MS1_DISABLE;
    MS2_DISABLE;
    DISABLE_STEP;
}

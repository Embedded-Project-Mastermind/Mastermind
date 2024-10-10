/*
 * joystick.h
 *
 *  Created on: 10 ott 2024
 *      Author: matteogottardelligmail.com
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include "graphics.h"

/* ADC results buffer */
static uint16_t resultsBuffer[2];
typedef enum {UP, DOWN, LEFT, RIGHT, CENTER} Move;
/* UP - Y>16200
 * DOWN - Y<200
 * LEFT - X<200
 * RIGHT - X >15500
 * CENTER - DEFAULT
 */

void NavigateMenu(Move direction);
void _adcInit();
void before_ADC();
void initHW();
Move findDirection(uint16_t x, uint16_t y);
#endif /* JOYSTICK_H_ */

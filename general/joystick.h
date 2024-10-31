/*
 * joystick.h
 *
 *  Created on: 10 ott 2024
 *      Author: matteogottardelligmail.com
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_
#include "graphics.h"
#define ADC14_CTL0_SREF_VREF_PLUS_AVCC  (0x00000000) // V+ = AVcc, V- = AVss
#define ADC14_CTL0_SHT_64_CLK             (0x00000000) // Sample time 64 ADC clocks
/* ADC results buffer */
static uint16_t resultsBuffer[2];
typedef enum {UP, DOWN, LEFT, RIGHT, CENTER} Move;
/* UP - Y>16200
 * DOWN - Y<200
 * LEFT - X<200
 * RIGHT - X >15500
 * CENTER - DEFAULT
 */
void upfunctions();
void downfunctions();
void leftfunctions();
void rightfunctions();
void Timer_Init(void);
void ADC_StartConversion(void);
void ADC_EnableInterrupts(void);
void setupPriorities();
void NavigateMenu(Move direction);
void _adcInit();
void before_ADC();
void initHW();
Move findDirection(uint16_t x, uint16_t y);
void delay_ms(uint32_t milliseconds);
#endif /* JOYSTICK_H_ */

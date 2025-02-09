/*
 * Title: joystick.h
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 27 ott 2024
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
/**
 * @brief Functions that handles the up stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void upfunctions();
/**
 * @brief Functions that handles the down stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void downfunctions();
/**
 * @brief Functions that handles the left stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void leftfunctions();
/**
 * @brief Functions that handles the right stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void rightfunctions();
/**
 * @brief Initialization of the timer corresponds to the first invocation of the timer and its functionality in order to measure the time passing
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void Timer_Init(void);
/**
 * @brief method that trigger the activation of the next read of ADC sensor
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void ADC_StartConversion(void);
/**
 * @brief enabling the interrupts for the two joystick channels P6.0 and P4.4
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void ADC_EnableInterrupts(void);
/**
 * @brief In order to handle the various interrupts, we have to setup the various sending of interrupts according to an hierarchy. If an interrupt with a higher priority arises, then the below level ones stops. The bottons, so the ports from 1 to 6 have the highest level, because is an instantaneous input, the timer a lower priority, because it has a period of time, but it is not always active, the adc of the joystick instead is always active and continously reads the input of it
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void setupPriorities();
/**
 * @brief According to the Enum declared redirects to one of the appove directional functions
 * @param direction Indicates the direction that each element performs according to the stick position
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void NavigateMenu(Move direction);
/**
 * @brief Initialization of the adc signal for the joystick, done activationg P6.0 and P4.4, an setting them up witht the tertiary mode
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void _adcInit();
/**
 * @brief Initialization of the adc signal for the joystick, done activationg P6.0 and P4.4, an setting them up witht the tertiary mode
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void before_ADC();
void initHW();
/**
 * @brief Choosing the direction of the joystick according to the position of it
 * @param x The x position from 0 on left to 15700 c.a. on right
 * @param y The y position from 0 on top to 16200 c.a. on bottom
 * @return Move gives and enum in order to determine visually to which category belongs that position
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
Move findDirection(uint16_t x, uint16_t y);
/**
 * @brief Function that stops the system for an amount of time, used primarly for synchronization
 * @param milliseconds Consists in the amount of time we desire to delay
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void delay_ms(uint32_t milliseconds);
#endif /* JOYSTICK_H_ */

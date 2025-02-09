/*
 * Title: input.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Matteo Gottardelli
 * Date Creation: 27 ott 2024
 */

#ifndef INPUT_H
#define INPUT_H

#include "msp.h"
#include "stdbool.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"

// Macros
//#define P1_D 0
#define P3_D 0
#define P4_D 1
#define P5_D 2
#define P6_D 3
#define DIMIO 32
#define BYTE 8

// Global variables
extern bool array[DIMIO];
extern bool buzzerBeepFlag;
extern uint8_t overflow_counter;

/**
 * @brief Function to reset the global bool array, simulating the activation of the ports
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void resetArrayInput(void);
/**
 * @brief Set array values based on the value inputed
 * @param val In case the value belongd to the interval 0 DIMIO, then it will be set to true, like an activation, instead it will mean that the try is over and it is reseted
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void setArrayInput(int val);
/**
 * @brief Setup the various ports from 1 to 6 in order, but not all the pins, because they have already active sensors connected to them, limitating the choice
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void configurePortsInput(void);
/**
 * @brief Setup the interrupt enabling only for some ports in order to make not append some undesired behavior
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void configureInterruptPortInput(void);
/**
 * @brief Verify how many inputs in a period of time were performed in the array generated
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
int counterTrue(void);
/**
 * @brief Verify the true input in a period of time, in order to see a clear output
 * @return int returning the array position that has a true value
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
int findTrue(void);
/**
 * @brief Determine which is the output action after pressing a button, it can be trigger a color or give a particular behavior if it is the back one or the confirm one
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void elaborateOutput(void);
/**
 * @brief Setup the timer TIMER A0 in order to be continuous tracking and usable to get some frames of time
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void configureTimersInput(void);
/**
 * @brief Verify on a specific port IFG which is the bit activated
 * @param status The IFG port status, that symbolizes the status of the pins on a port
 * @return returns a uint8 corresponding to the actual bit position searched in the status
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
uint8_t bitofstatus(uint8_t status);
/**
 * @brief Sets the position of the array according to an input pin on a port
 * @param status The IFG port status, that symbolizes the status of the pins on a port
 * @param port The port, that could not correspond to the reality, but to a convension with the define in .h file
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void switching(uint8_t status, int8_t port);
/**
 * @brief Verify that there is only one true input in a period of time, in order to see a clear output
 * @return bool returning the result TRUE if there was only one input and FALSE if not
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
bool atLeastOneTrue(void);
/**
 * @brief A via for creating a dummy trigger on P1.1, in order to reactivate an undesired stop of the system
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-05
 */
void triggerPinInterrupt();

#endif // INPUT_H

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

// Function declarations
void resetArrayInput(void);
void setArrayInput(int val);
void configurePortsInput(void);
void configureInterruptPortInput(void);
int counterTrue(void);
int findTrue(void);
void elaborateOutput(void);
void configureTimersInput(void);
uint8_t bitofstatus(uint8_t status);
void switching(uint8_t status, int8_t port);
bool atLeastOneTrue(void);
void triggerPinInterrupt();

#endif // INPUT_H

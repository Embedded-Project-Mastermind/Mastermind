/*
 * graphics.h
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 *      //0. SETUP ENVIRONMENT
     * Search the four files sent on Whatsapp and save them in a folder called LcdDriver
     * Create a project CCS and setup the machine for MSP432P401R
     * Add the folder previously created in the project
     * Download and install simplelink for mps432 on ti.com, based on your OS
     * Go on the properties right-clicking on the created project
     * In the left column select Build > Arm Compiler > Include Options
     * In add dir to #include search path click the add file icon and then Browse
     * Search the simplelink_msp432p4_sdk_3_40_01_02 folder. If you can't find it, go on Applications > ti
     * In this folder follow this path simplelink_msp432p4_sdk_3_40_01_02 > source and click on open and then OK
     * Then, always in the left column select Build > Arm Linker > File Search Path
     * In include library file or command file as input click the add file icon and then Browse
     * You will have to do this twice with two different paths, but first search the simplelink folder:
     * 1. simplelink_msp432p4_sdk_3_40_01_02 > source > ti > devices > mps432p4xx > driverlib > ccs > msp432p4xx_driverlib.lib
     * 2. simplelink_msp432p4_sdk_3_40_01_02 > source > ti > grlib > lib > ccs > m4 > grlib.a
     * After adding the files successfullt, click bottom-right apply and close
     * Finally, rebuild the project and try to check out if this file pasted in main.c generates errors
 */

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <stdbool.h>
//1. DEFINITION OF CONTEXT
Graphics_Context grContext;
//2. DEFINITION OF COLORS

//BACKGROUND COLORS
const int32_t BACKGROUND_STANDARD_COLOR=GRAPHICS_COLOR_BLACK;
const int32_t BACKGROUND_FOCUSED_COLOR=GRAPHICS_COLOR_BLACK;
const int32_t BACKGROUND_SELECTED_COLOR=GRAPHICS_COLOR_WHITE;

//FOREGROUND COLORS
const int32_t FOREGROUND_STANDARD_COLOR=GRAPHICS_COLOR_WHITE;
const int32_t FOREGROUND_FOCUSED_COLOR=GRAPHICS_COLOR_RED;
const int32_t FOREGROUND_SELECTED_COLOR=GRAPHICS_COLOR_BLACK;

typedef enum Graphics_State {START, DIMENSION, DIFFICULTY, TENTATIVE, DOUBLES, INFO, GAME, CHRONOLOGY, END} Graphics_State;

typedef enum Button_State {STANDARD, FOCUSED, SELECTED} Button_State;

typedef struct Graphics_Text {
    int8_t* string;
    int16_t x;
    int16_t y;
    bool opacity;
} Graphics_Text;

typedef struct Graphics_Circle {
    int16_t x;
    int16_t y;
    int16_t radius;
    int32_t color;
} Graphics_Circle;

typedef struct Graphics_Button {
    Button_State state;
    Graphics_Rectangle rect;
    Graphics_Text text;
} Graphics_Button;

#endif /* GRAPHICS_H_ */

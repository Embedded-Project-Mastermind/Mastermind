/*
 * Title: fsm.h
 * Primary Authors: Alessandro Benassi, Daniele Calvo, Matteo Gottardelli, Niccolò Cristoforetti
 * Helpers: -
 • Maintainability: Alessandro Benassi, Daniele Calvo, Matteo Gottardelli, Niccolò Cristoforetti
 * Date Creation: 5 ott 2024
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
#include <fsm.h>
//1. DEFINITION OF CONTEXT
Graphics_Context grContext;
//2. DEFINITION OF COLORS
//BACKGROUND COLORS
#define BACKGROUND_STANDARD_COLOR GRAPHICS_COLOR_WHITE

//FOREGROUND COLORS
#define SELECTED_COLOR GRAPHICS_COLOR_WHITE
#define STANDARD_COLOR GRAPHICS_COLOR_BLACK
#define DISABLED_COLOR GRAPHICS_COLOR_GRAY
#define BORDER_FOCUSED_COLOR GRAPHICS_COLOR_RED
#define BORDER_SELECTED_COLOR GRAPHICS_COLOR_BLACK
#define FILL_UPPER_RECT GRAPHICS_COLOR_BLUE
#define FILL_MOVEMENT GRAPHICS_COLOR_CYAN
#define STANDARD_TEXT GRAPHICS_COLOR_BLACK

//Enum Declaration for display changes
typedef enum Graphics_State {START_GR, DIMENSION, DIFFICULTY, TENTATIVE, DOUBLES, INFO, GAME, CHRONOLOGY, END, ERROR_GR} Graphics_State;
//Button possible states
typedef enum Button_State {STANDARD, FOCUSED, SELECTED, DISABLED} Button_State;
//Struct Declarations
typedef struct Graphics_Text {
    int8_t* string; //Content of the text
    //int16_t x; //upper-left corner x position
    //int16_t y; //upper-left corner x position
    bool opacity; //0 no opacity, 1 yes opacity
} Graphics_Text;

typedef struct Graphics_Circle {
    int16_t x; //Center of figure x position
    int16_t y; //Center of figure y position
    int16_t radius; //Radius of figure
    int32_t color; //Fill color of the figure
} Graphics_Circle;

typedef struct Graphics_Button {
    Button_State state; //Current button state
    Graphics_Rectangle rect; //Rectangle Struct
    Graphics_Text text; //A positioned text with a content inside
} Graphics_Button;
//Extern Variables
extern Graphics_State display_position;
extern int8_t sizes[ERROR_GR];
#endif /* GRAPHICS_H_ */



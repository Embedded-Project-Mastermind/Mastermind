/*
 * implementations.h
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 */

#ifndef IMPLEMENTATIONS_H_
#define IMPLEMENTATIONS_H_
#include "stdio.h"
#include "stdlib.h"
#include "graphics.h"
#define BORDER 2

void graphics_Init(void);
void hardware_Init(void);
void reset_Screen(void);
//FOLLOWING DEFINE THE GRAPHIC FUNCTIONS USED IN C FILE
extern Graphics_Rectangle upperRect;
extern Graphics_Button prevButton;
extern Graphics_Button nextButton;
extern Graphics_Text labelText;
extern uint8_t position;
//FIND POSITION RECT
int32_t getCenteredX(Graphics_Rectangle rect);
int32_t getCenteredY(Graphics_Rectangle rect);
//COLOR CHOICE FUNCTIONS
int32_t chooseColorRect(Button_State state, int32_t color);
int32_t chooseColorText(Button_State state, int32_t color);
//FUNCTIONS DRAW
void defaultDraw(void);
void drawDimension(void);
void focusedHandle(void);
//FUNCTIONS FOR STATES
void fn_START_GR(void);
void fn_DIMENSION(void);
void fn_DIFFICULTY(void);
void fn_TENTATIVE(void);
void fn_DOUBLES(void);
void fn_INFO(void);
void fn_GAME(void);
void fn_CHRONOLOGY(void);
void fn_END(void);
#endif /* IMPLEMENTATIONS_H_ */

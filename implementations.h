/*
 * Title: implementations.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Niccolò Cristoforetti
 * Maintainability: Matteo Gottardelli
 * Date Creation: 5 ott 2024
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
extern Graphics_Rectangle upperRectCH;
extern Graphics_Text labelText;
extern uint8_t position;
//FIND POSITION RECT
int32_t getCenteredX(Graphics_Rectangle rect);
int32_t getCenteredY(Graphics_Rectangle rect);
//COLOR CHOICE FUNCTIONS
int32_t chooseColorRect(Button_State state, int32_t color);
int32_t chooseColorText(Button_State state, int32_t color);
//FUNCTIONS STATUS
void handleOut(Graphics_Button array[], uint8_t position, int8_t size);
void handleIn(Graphics_Button array[], uint8_t position, int8_t size);
//FUNCTIONS DRAW
void rectangleWithText(Graphics_Rectangle rect, int32_t colorRect, Graphics_Text text, int32_t colorText);
int8_t findSelected(Graphics_Button array[], int8_t size);
void drawButton(Graphics_Button button, int32_t rect_color, int32_t text_color, int8_t pos_selected);
void focusedHandle(Button_State state, Graphics_Rectangle rect, int32_t color);
void handleSelection(Graphics_Button array[]);
void handleDeselection(Graphics_Button array[]);
//buttons back and next handler
void handle_buttons(Graphics_Button array[]);
//FUNCTION INIT
void initArray(Graphics_Button array[], int size);
//FUNCTIONS FOR STATES
#endif /* IMPLEMENTATIONS_H_ */

/*
 * Title: difficulty.h
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 10 ott 2024
 */

#ifndef DIFFICULTY_H_
#define DIFFICULTY_H_
#include "stdio.h"
#include "stdlib.h"
#include "implementations.h"
#define DIFF_DIM 20
#define DIFF_TEXT 4
#define DIFF_TYPES 4

void fn_DIFFICULTY(void);
void drawDifficulty();
void upStick_DIFFICULTY();
void downStick_DIFFICULTY();
void leftStick_DIFFICULTY();
void rightStick_DIFFICULTY();
void handlePressure_DIFFICULTY();

extern Graphics_Button diff_buttons[];
extern Graphics_Text explain[DIFF_TEXT][DIFF_TYPES];
#endif /* DIFFICULTY_H_ */

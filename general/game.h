/*
 * Title: game.h
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Alessandro Benassi, Matteo Gottardelli
 * Date Creation: 31 ott 2024
 */

#ifndef GAME_H_
#define GAME_H_
#include "graphics.h"
#include "implementations.h"
#include "input.h"
#define YLEVEL_OFFSET 32
extern bool configurationGame;

extern Graphics_Circle circles[];
extern Graphics_Rectangle textRect;
extern int16_t color_selected;
void fn_GAME(void);
void elaborateColor(int16_t c);
void initCircles();
void populateCircles(int16_t offset, int16_t radius, int16_t value_y);
void drawCircles(Graphics_Circle* circs);
void leftStick_GAME();
int32_t selectColor(int16_t color);
void displayResultsOnScreen();
#endif /* GAME_H_ */

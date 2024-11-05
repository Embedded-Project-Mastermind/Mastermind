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

extern bool configurationGame;
extern int16_t color_selected;
extern Graphics_Circle circles[];

void fn_GAME(void);
void elaborateColor(int16_t c);
void initCircles();
void populateCircles(int16_t offset, int16_t radius);
void drawCircles();


#endif /* GAME_H_ */

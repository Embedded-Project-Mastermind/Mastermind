/*
 * game.h
 *
 *  Created on: 27 ott 2024
 *      Author: matteogottardelligmail.com
 */

#ifndef GAME_H_
#define GAME_H_
#include "graphics.h"
#include "implementations.h"
#include "input.h"

extern bool configurationGame;

extern Graphics_Circle circles[];

void fn_GAME(void);
void elaborateColor(int16_t c);
void initCircles();
void populateCircles(int16_t offset, int16_t radius);
void drawCircles();


#endif /* GAME_H_ */

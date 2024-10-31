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
extern int16_t color_selected;

void fn_GAME(void);
void elaborateColor(int8_t c);

#endif /* GAME_H_ */

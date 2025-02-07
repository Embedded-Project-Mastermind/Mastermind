/*
 * Title: end.h
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 7 nov 2024
 */

#ifndef END_H_
#define END_H_
#include "stdio.h"
#include "stdlib.h"
#include "fsm.h"
#include "implementations.h"
#include "graphics.h"
#include "bitmap.h"
#include "start.h"


extern Graphics_Button gameover_button;
extern Graphics_Button win_button;

void drawEnd(int elems);
void fn_END(void);
uint16_t encodeColor(uint8_t r, uint8_t g, uint8_t b);
#endif /* START_H_ */

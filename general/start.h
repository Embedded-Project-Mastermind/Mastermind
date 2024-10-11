/*
 * chronology.h
 *
 *  Created on: 10 ott 2024
 *      Author: niccolocristoforetti
 */

#ifndef START_H_
#define START_H_
#include "stdio.h"
#include "stdlib.h"
#include "implementations.h"
#include "graphics.h"
#include "bitmap.h"

#define CHRONO_DIM 32

extern Graphics_Button start_button;

void drawStart(int elems);
void fn_START_GR(void);
void drawPixel(uint32_t x, uint32_t y, const uint8_t color);
//void drawImage(uint32_t x, uint32_t y);

#endif /* START_H_ */

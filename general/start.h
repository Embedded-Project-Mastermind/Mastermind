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

#define UPPER_LEFT_X 18
#define UPPER_LEFT_Y 16

extern Graphics_Button start_button;

void drawStart(int elems);
void fn_START_GR(void);
uint16_t encodeColor(uint8_t r, uint8_t g, uint8_t b);
//void drawImage(uint32_t x, uint32_t y);
static const Graphics_Image grImage={
      .bPP=IMAGE_FMT_8BPP_UNCOMP,
      .numColors=256,
      .pPalette=(const uint32_t *)palette,
      .pPixel=(const uint8_t *)image,
      .xSize=SIZE_IMAGE_X,
      .ySize=SIZE_IMAGE_Y

};
#endif /* START_H_ */

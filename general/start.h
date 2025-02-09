/*
 * Title: start.c
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: Matteo Gottardelli
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 10 ott 2024
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

/**
 * @brief draws the start screen, including the start button and an image
 * @param
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void drawStart(int elems);
/**
 * @brief encodes an RGB color into a 16-bit format suitable for the display
 * @param red presence in the pixel
 * @param green presence in the pixel
 * @param blue presence in the pixel
 * @return single 16-bit color code for the display
 * @author Niccolò Cristoforetti (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void fn_START_GR(void);
/**
 * @brief initializes and displays the start screen
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
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

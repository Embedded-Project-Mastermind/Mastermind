/*
 * Title: start.c
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: Matteo Gottardelli
 * Maintainability: Daniele Calvo
 * Date Creation: 10 ott 2024
 */
#include "start.h"
#include "implementations.h"
#include "graphics.h"

/**
 * @brief draws the start screen, including the start button and an image
 * @param
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void drawStart(int elems) {
     drawButton(start_button, STANDARD_COLOR, SELECTED_COLOR, -1);
     //Graphics_drawImage(&grContext, &grImage, UPPER_LEFT_X, UPPER_LEFT_Y);
     uint16_t x, y;
     for (y = 0; y < grImage.ySize; y++) {
         for (x = 0; x < grImage.xSize; x++) {
             uint8_t colorIndex = grImage.pPixel[y * grImage.xSize + x]; // Access the pixel data

             // Retrieve color from palette
             uint8_t r = palette[colorIndex][0];
             uint8_t g = palette[colorIndex][1];
             uint8_t b = palette[colorIndex][2];

             // Call your function to draw the pixel on the display
             Graphics_drawPixelOnDisplay(grContext.display, x+UPPER_LEFT_X, y+UPPER_LEFT_Y, encodeColor(r,g,b));
             Graphics_flushBuffer(&grContext);
         }
     }
}
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
uint16_t encodeColor(uint8_t r, uint8_t g, uint8_t b) {
    // Ensure the values are clamped to the correct range
    if (r > 31) r = 31; // 5 bits can hold values from 0 to 31
    if (g > 63) g = 63; // 6 bits can hold values from 0 to 63
    if (b > 31) b = 31; // 5 bits can hold values from 0 to 31

    // Combine the values into a single uint16_t
    return (uint16_t)( (g << 10) | (r << 5) | b );
}
/**
 * @brief initializes and displays the start screen
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void fn_START_GR(void) {
    reset_Screen();
    Graphics_setBackgroundColor(&grContext, STANDARD_COLOR);
    Graphics_clearDisplay(&grContext);
    //DRAW FUNCTION
    drawStart(sizes[START_GR]);
    //FOLLOWING POSITION
}

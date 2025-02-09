/*
 * Title: end.c
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Daniele Calvo
 * Date Creation: 7 nov 2024
 */
#include "end.h"
#include "implementations.h"
#include "graphics.h"

/**
 * @brief draws the end screen, displaying either a win or game over message.
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-11-07
 */
void drawEnd() {
    if(current_state==WIN){
        drawButton(win_button, STANDARD_COLOR, SELECTED_COLOR, -1);
    } else {
        drawButton(gameover_button, STANDARD_COLOR, SELECTED_COLOR, -1);
    }
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
 * @brief initializes and displays the end screen
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-11-07
 */
void fn_END(void) {
    reset_Screen();
    Graphics_setBackgroundColor(&grContext, STANDARD_COLOR);
    Graphics_clearDisplay(&grContext);
    //DRAW FUNCTION
    drawEnd();
    //FOLLOWING POSITION
}

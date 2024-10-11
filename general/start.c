/*
 * start.c
 *
 *  Created on: 10 ott 2024
 *      Author: niccolocristoforetti
 */
#include "start.h"
#include "implementations.h"
#include "graphics.h"

void drawStart(int elems) {
     drawButton(start_button, STANDARD_COLOR, SELECTED_COLOR);
     int i;
     int j;
     for(i=0; i<SIZE_IMAGE; i++){
         for(j=0; j<SIZE_IMAGE; j++){
             //drawPixel(i, j, bitmap_PersonalImage[i][j]);
         }
     }
}

void fn_START_GR(void) {
    reset_Screen();
    //DRAW FUNCTION
    reset_Screen();
    int32_t num_elements=1; //(sizeof(diff_buttons)/sizeof(diff_buttons[0]));
    drawStart(num_elements);
    //FOLLOWING POSITION
}

void drawPixel(uint32_t x, uint32_t y, const uint8_t color){
    //Graphics_drawPixel(&grContext, x, y, color);
}

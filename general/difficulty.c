/*
 * difficulty.c
 *
 *  Created on: 10 ott 2024
 *      Author: matteogottardelligmail.com
 */


#include "difficulty.h"

void drawDifficulty(int32_t elems) {
    int i;
    for (i=0; i<elems; i++) {
        if (i<elems-2) {
            drawButton(diff_buttons[i], STANDARD_COLOR, SELECTED_COLOR);
        }
        else {
            drawButton(diff_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);
        }
    }
}
void drawText() {
    Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
    int i;
    for (i=0; i<4; i++) {//Logic implementation
        Graphics_drawString(&grContext, (int8_t *)explain[i][position].string, AUTO_STRING_LENGTH, DIFF_DIM+5,  32+5+10*i, explain[i][position].opacity);
    }
}

void fn_DIFFICULTY(void) {
    reset_Screen();
    int32_t num_elements=5; //Logic implementation
    diff_buttons[num_elements-2]=prevButton;
    diff_buttons[num_elements-1]=nextButton;
    defaultDraw();
    drawDifficulty(num_elements);
    drawText();
}

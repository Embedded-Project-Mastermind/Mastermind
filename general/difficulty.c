/*
 * difficulty.c
 *
 *  Created on: 10 ott 2024
 *      Author: matteogottardelligmail.com
 */


#include "difficulty.h"
#include "implementations.h"
void drawDifficulty() {
    int i;
    for (i=0; i<sizes[DIFFICULTY]; i++) {
        if (i<sizes[DIFFICULTY]-2) {
            drawButton(diff_buttons[i], STANDARD_COLOR, SELECTED_COLOR);
        }
        else {
            drawButton(diff_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);
        }
    }
}
void drawText() {
    Graphics_Rectangle temp={DIFF_DIM+2, 32+1, 128-1, 96-1};
    Graphics_setForegroundColor(&grContext, STANDARD_COLOR);
    Graphics_fillRectangle(&grContext, &temp);
    Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
    int i;
    for (i=0; i<DIFF_TEXT; i++) {//Logic implementation
        Graphics_drawString(&grContext, (int8_t *)explain[i][position].string, AUTO_STRING_LENGTH, DIFF_DIM+10,  32+10+10*i, explain[i][position].opacity);
    }
}

void fn_DIFFICULTY(void) {
    reset_Screen();
    diff_buttons[sizes[DIFFICULTY]-2]=prevButton;
    diff_buttons[sizes[DIFFICULTY]-1]=nextButton;
    defaultDraw();
    drawDifficulty();
    drawText();
}
void upStick_DIFFICULTY() {
    if(position>0 && position<sizes[DIFFICULTY]-2) {
        handleOut(diff_buttons, position);
        position--;
        handleIn(diff_buttons, position);
        drawText();
    }
    else if (position>=sizes[DIFFICULTY]-2) {
        handleOut(diff_buttons, position);
        position=2;
        handleIn(diff_buttons, position);
        drawText();
    }
}
void downStick_DIFFICULTY() {
    if(position<3) {
        handleOut(diff_buttons, position);
        position++;
        handleIn(diff_buttons, position);
        drawText();
    }
}
void leftStick_DIFFICULTY() {

}
void rightStick_DIFFICULTY() {

}

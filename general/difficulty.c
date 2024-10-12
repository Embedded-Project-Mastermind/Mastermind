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
            drawButton(diff_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(diff_buttons, sizes[DIFFICULTY]));
        }
        else {
            drawButton(diff_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(diff_buttons, sizes[DIFFICULTY]));
        }
    }
}
void drawText() {
    Graphics_Rectangle temp={DIFF_DIM+2, 32+1, 128-1, 96-1};
    Graphics_setForegroundColor(&grContext, STANDARD_COLOR);
    Graphics_fillRectangle(&grContext, &temp);
    Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
    if (position<sizes[DIFFICULTY]-1) {
        int i;
        for (i=0; i<DIFF_TEXT; i++) {//Logic implementation
            Graphics_drawString(&grContext, (int8_t *)explain[i][position].string, AUTO_STRING_LENGTH, DIFF_DIM+10,  32+10+10*i, explain[i][position].opacity);
        }
    }
}

void fn_DIFFICULTY(void) {
    reset_Screen();
    initArray(diff_buttons, sizes[DIFFICULTY]);
    defaultDraw();
    drawDifficulty();
    drawText();
}
void upStick_DIFFICULTY() {
    if(position>0 && position<(sizes[DIFFICULTY]-2)) {
        handleOut(diff_buttons, position, sizes[DIFFICULTY]);
        position--;
        handleIn(diff_buttons, position, sizes[DIFFICULTY]);
        drawText();
    }
    else {
        if ((position==sizes[DIFFICULTY]-2) || (position==sizes[DIFFICULTY]-1)){
            handleOut(diff_buttons, position, sizes[DIFFICULTY]);
            position=sizes[DIFFICULTY]-3;
            handleIn(diff_buttons, position, sizes[DIFFICULTY]);
            drawText();
        }
    }
}
void downStick_DIFFICULTY(){
    if(position<(sizes[DIFFICULTY]-2)){
        handleOut(diff_buttons, position, sizes[DIFFICULTY]);
        position++;
        handleIn(diff_buttons, position, sizes[DIFFICULTY]);
        drawText();
    }
}
void leftStick_DIFFICULTY() {
    if (position==sizes[DIFFICULTY]-1) {
        handleOut(diff_buttons, position, sizes[DIFFICULTY]);
        position--;
        handleIn(diff_buttons, position, sizes[DIFFICULTY]);
    }
}
void rightStick_DIFFICULTY() {
    if (position==sizes[DIFFICULTY]-2 && (diff_buttons[sizes[DIFFICULTY-1]].state!=DISABLED)) {
            handleOut(diff_buttons, position, sizes[DIFFICULTY]);
            position++;
            handleIn(diff_buttons, position, sizes[DIFFICULTY]);

      }
}

void handlePressure_DIFFICULTY() {
    game.difficulty=diff_buttons[position].text.string[0];
    handleSelection(diff_buttons);
}

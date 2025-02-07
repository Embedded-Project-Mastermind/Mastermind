/*
 * Title: difficulty.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 10 ott 2024
 */


#include "difficulty.h"
#include "implementations.h"

Graphics_Text explain[][DIFF_TYPES]={
     {{"EASY MODE", false},{"MEDIUM MODE", false}, {"HARD MODE", false}},
     {{"INFO PER COLOR", false},{"INFO GENERAL", false},{"INFO GENERAL", false}},
     {{"- RIGHT POS", false},{"- RIGHT POS", false},{"- RIGHT POS", false}},
     {{"- WRONG POS", false}, {"- WRONG POS", false}, {"", false}}
};

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
    int8_t i;
    if (position<sizes[DIFFICULTY]-2) {
        for (i=0; i<DIFF_TEXT; i++) {//Logic implementation
            Graphics_drawString(&grContext, (int8_t *)explain[i][position].string, AUTO_STRING_LENGTH, DIFF_DIM+10,  32+10+10*i, explain[i][position].opacity);
        }
    }
    else {
        int8_t selected=findSelected(diff_buttons, sizes[DIFFICULTY]);
        if (selected>=0) {
            for (i=0; i<DIFF_TEXT; i++) {
                Graphics_drawString(&grContext, (int8_t *)explain[i][(int) selected].string, AUTO_STRING_LENGTH, DIFF_DIM+10,  32+10+10*i, explain[i][selected].opacity);
            }
        }
    }
}

void fn_DIFFICULTY(void) {
    reset_Screen();
    initArray(diff_buttons, sizes[DIFFICULTY]);
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
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
        drawText();
    }
}
void rightStick_DIFFICULTY() {
    if (position==sizes[DIFFICULTY]-2 && (diff_buttons[sizes[DIFFICULTY-1]].state!=DISABLED)) {
            handleOut(diff_buttons, position, sizes[DIFFICULTY]);
            position++;
            handleIn(diff_buttons, position, sizes[DIFFICULTY]);
            drawText();
      }
}

void handlePressure_DIFFICULTY() {
    game.difficulty=diff_buttons[position].text.string[0];
    handleSelection(diff_buttons);
}

/*
 * tentatives.c
 *
 *  Created on: 10 ott 2024
 *      Author: niccolocristoforetti
 */
#include "tentatives.h"
#include "implementations.h"
#include "graphics.h"

void drawTentatives(int elems) {
    int i;
       for (i=0; i<elems; i++) {
           if (i<elems-2) {
               drawButton(tent_buttons[i], STANDARD_COLOR, SELECTED_COLOR);
           }
           else {
               drawButton(tent_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);
           }
       }
}

void fn_TENTATIVE(void) {
    reset_Screen();
    //DRAW FUNCTION
    reset_Screen();
    int32_t num_elements=9; //(sizeof(diff_buttons)/sizeof(diff_buttons[0]));
    tent_buttons[num_elements-2]=prevButton;
    tent_buttons[num_elements-1]=nextButton;
    defaultDraw();
    drawTentatives(num_elements);
    //FOLLOWING POSITION
}


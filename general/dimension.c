/*
 * dimension.c
 *
 *  Created on: 10 ott 2024
 *      Author: AlessandroBenassi
 */
#include "dimension.h"
#include "implementations.h"

void drawDimension(int32_t elems) {
    int i;
    for (i=0; i<elems; i++) {
        if (i<elems-2) {
            Graphics_setFont(&grContext, &g_sFontCm20);
            drawButton(dim_buttons[i], STANDARD_COLOR, SELECTED_COLOR);
        }
        else {
            Graphics_setFont(&grContext, &g_sFontFixed6x8);
            drawButton(dim_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);
        }
    }
}

void fn_DIMENSION(void) {
    reset_Screen();

    int32_t num_elements = 6;  // 6 elements, 4 buttons for dimension selection and back and next buttons
    dim_buttons[num_elements-2]=prevButton; //add prev to the array
    dim_buttons[num_elements-1]=nextButton;  //add back to the array
    defaultDraw(); //default draw function, draws top part, back and next buttons

    drawDimension(num_elements);
    //FOLLOWING POSITION
}


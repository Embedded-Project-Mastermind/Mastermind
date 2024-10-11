/*
 * dimension.c
 *
 *  Created on: 10 ott 2024
 *      Author: AlessandroBenassi
 */
#include "dimension.h"
#include "implementations.h"

void drawDimension() {
    int i;
    for (i=0; i<sizes[DIMENSION]; i++) {
        if (i<sizes[DIMENSION]-2) {
            Graphics_setFont(&grContext, &g_sFontCm20);
            drawButton(dim_buttons[i], STANDARD_COLOR, SELECTED_COLOR);
        }
        else {
            Graphics_setFont(&grContext, &g_sFontFixed6x8);
            drawButton(dim_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);
        }
    }
}

void handleFont(){
    if (position<sizes[DIMENSION]-2) {
        Graphics_setFont(&grContext, &g_sFontCm20);
    }
    else{
        Graphics_setFont(&grContext, &g_sFontFixed6x8);
    }
}

void fn_DIMENSION(void) {
    reset_Screen();  //screen reset function
//    int32_t num_elements = 6;  // 6 elements, 4 buttons for dimension selection and back and next buttons
    dim_buttons[sizes[DIMENSION]-2]=prevButton; //add prev to the array
    dim_buttons[sizes[DIMENSION]-1]=nextButton;  //add back to the array
    defaultDraw(); //default draw function, draws top part, back and next buttons
    drawDimension();
    //FOLLOWING POSITION
}

void upStick_DIMENSION(){
    if(position>1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position-2;
        handleFont(); //sarebbe da ottimizzare
        handleIn(dim_buttons, position);
    }
}

void downStick_DIMENSION(){
    if(position<3){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position=position+2;
            handleFont();
            handleIn(dim_buttons, position);
    }
    else if(position==3 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED ){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position+2;
        handleFont();
        handleIn(dim_buttons, position);
    }
}

void leftStick_DIMENSION(){
    //int num=position%2;
    if((position%2)==1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position--;
        handleFont();
        handleIn(dim_buttons, position);
    }
}

void rightStick_DIMENSION(){
    //int num=position%2;
    if((position%2)==0){
        if(position<4){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position++;
            handleFont();
            handleIn(dim_buttons, position);
        }
        if(position==4 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED){
           handleFont();
           handleOut(dim_buttons, position, sizes[DIMENSION]);
           position++;
           handleFont();
           handleIn(dim_buttons, position);
       }
     }
}






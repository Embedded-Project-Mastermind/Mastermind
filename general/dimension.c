/*
 * Title: difficulty.c
 * Primary Authors: Alessandro Benassi
 * Helpers: -
 * Maintainability: Alessandro Benassi
 * Date Creation: 10 ott 2024
 */
#include "dimension.h"
#include "implementations.h"

void drawDimension() {
    int i;
    for (i=0; i<sizes[DIMENSION]; i++) {
        if (i<sizes[DIMENSION]-2) {
            Graphics_setFont(&grContext, &g_sFontCm20);
            drawButton(dim_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(dim_buttons, sizes[DIMENSION]));
        }
        else {
            Graphics_setFont(&grContext, &g_sFontFixed6x8);
            drawButton(dim_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(dim_buttons, sizes[DIMENSION]));
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
    initArray(dim_buttons, sizes[DIMENSION]);
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR); //default draw function, draws top part, back and next buttons
    drawDimension();
    //FOLLOWING POSITION
}

void upStick_DIMENSION(){
    if(position>1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position-2;
        handleFont(); //sarebbe da ottimizzare
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}

void downStick_DIMENSION(){
    if(position<3){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position=position+2;
            handleFont();
            handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
    else if(position==3 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED ){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position+2;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}

void leftStick_DIMENSION(){
    //int num=position%2;
    if((position%2)==1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position--;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
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
            handleIn(dim_buttons, position, sizes[DIMENSION]);
        }
        if(position==4 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED){
           handleFont();
           handleOut(dim_buttons, position, sizes[DIMENSION]);
           position++;
           handleFont();
           handleIn(dim_buttons, position, sizes[DIMENSION]);
       }
     }
}
void handlePressure_DIMENSION() {
    game.dim=atoi((char*)dim_buttons[position].text.string);
    handleSelection(dim_buttons);
}





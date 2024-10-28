/*
 * dimension.c
 *
 *  Created on: 10 ott 2024
 *      Author: AlessandroBenassi
 */
#include "dimension.h"
#include "implementations.h"

void drawDimension() {  //draws thew scenenario
    int i;
    for (i=0; i<sizes[DIMENSION]; i++) { //uses sizes[] funciton to calculate the size of the array of buttons
        if (i<sizes[DIMENSION]-2) { //draws back and next button
            Graphics_setFont(&grContext, &g_sFontCm20);
            drawButton(dim_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(dim_buttons, sizes[DIMENSION]));
        }
        else { draws the other buttons
            Graphics_setFont(&grContext, &g_sFontFixed6x8);
            drawButton(dim_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(dim_buttons, sizes[DIMENSION]));
        }
    }
}

void handleFont(){ //manages the font dimension for the buttons
    if (position<sizes[DIMENSION]-2) { //normal font for next and back buttons
        Graphics_setFont(&grContext, &g_sFontCm20);
    }
    else{ //bigger font for the selection buttons to see better
        Graphics_setFont(&grContext, &g_sFontFixed6x8);
    }
}

void fn_DIMENSION(void) { //general function for sceneario drawing
    reset_Screen();  //screen reset function
    initArray(dim_buttons, sizes[DIMENSION]);
    defaultDraw(); //default draw function, draws top part, back and next buttons
    drawDimension();
    //FOLLOWING POSITION
}

void upStick_DIMENSION(){ //handles the up movement of the stick
    if(position>1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position-2;
        handleFont(); //sarebbe da ottimizzare
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}

void downStick_DIMENSION(){  //handles the down movement of the stick
    if(position<3){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position=position+2;
            handleFont();
            handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
    else if(position==3 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED ){ //handles the case of next button disabled
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position+2;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}

void leftStick_DIMENSION(){  //handles the left movement of the stick
    //int num=position%2;
    if((position%2)==1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position--;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}

void rightStick_DIMENSION(){  //handles the right movement of the stick
    //int num=position%2;
    if((position%2)==0){
        if(position<4){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position++;
            handleFont();
            handleIn(dim_buttons, position, sizes[DIMENSION]);
        }
        if(position==4 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED){ //handles the case of next button disabled
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





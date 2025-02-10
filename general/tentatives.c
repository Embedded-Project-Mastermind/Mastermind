/*
 * Title: tentatives.c
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 10 ott 2024
 */
#include "tentatives.h"
#include "implementations.h"
#include "graphics.h"

Graphics_Button other_things[]={
    {DISABLED, {TENT_DIM+1, 32+2, TENT_DIM*4-1, 32+TENT_DIM-1}, {"NO TENT", false}},
    {DISABLED, {1, 32+2, TENT_DIM-1, 32+TENT_DIM-1}, {"", false}}
};

/**
 * @brief function that create buttons and text for the Tentatives screen
 * @param integer for the number of buttons of the Tentatives screen
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawTentatives(int elems) {
    int i;
    for (i=0; i<2; i++) {
        drawButton(other_things[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(tent_buttons, sizes[TENTATIVE]));
    }
    for (i=0; i<elems; i++) {
           if (i<elems-2) {
               drawButton(tent_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(tent_buttons, sizes[TENTATIVE]));
           }
           else {
               drawButton(tent_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(tent_buttons, sizes[TENTATIVE]));
           }
       }
}

/**
 * @brief functions that create the tentatives screen starting from resetting the previous screen
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void fn_TENTATIVE(void) {
    reset_Screen();
    //DRAW FUNCTION
    reset_Screen();
    initArray(tent_buttons, sizes[TENTATIVE]);
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
    drawTentatives(sizes[TENTATIVE]);
}

/**
 * @brief manage what to do when the user moves the stick up
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void upStick_TENTATIVE() {
    if(position>=1 && position<=4) {
        handleOut(tent_buttons, position, sizes[TENTATIVE]);
        position=0;
        handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
    else if (position==sizes[TENTATIVE]-2) {
        handleOut(tent_buttons, position, sizes[TENTATIVE]);
        if(tent_buttons[1].state!=DISABLED){
            position=1;
        } else{
            position=0;
        }
        handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
    else if (position==sizes[TENTATIVE]-1) {
            handleOut(tent_buttons, position, sizes[TENTATIVE]);
            if(tent_buttons[3].state!=DISABLED){
              position=3;
            } else{
              position=0;
            }
            handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
}

/**
 * @brief manage what to do when the user moves the stick down
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void downStick_TENTATIVE() {
    if(position==0) {
        handleOut(tent_buttons, position, sizes[TENTATIVE]);
        if(tent_buttons[1].state!=DISABLED){
             position=1;
        } else{
             position=sizes[TENTATIVE]-2;
        }
        handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
    else if(position==1 || position==2) {
            handleOut(tent_buttons, position, sizes[TENTATIVE]);
            position=sizes[TENTATIVE]-2;
            handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
    else if(position==3 || position==4) {
            handleOut(tent_buttons, position, sizes[TENTATIVE]);
            if(tent_buttons[sizes[TENTATIVE]-1].state!=DISABLED){
              position=sizes[TENTATIVE]-1;
            } else{
              position=sizes[TENTATIVE]-2;
            }
            handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
}

/**
 * @brief manage what to do when the user moves the stick to the left
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void leftStick_TENTATIVE() {
    if(position>=1 && position<sizes[TENTATIVE]) {
            handleOut(tent_buttons, position, sizes[TENTATIVE]);
            int i=position-1;
            while(tent_buttons[i].state==DISABLED){
                i--;
            }
            position=i;
            handleIn(tent_buttons, position, sizes[TENTATIVE]);
    }
}

/**
 * @brief manage what to do when the user moves the stick to the right
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void rightStick_TENTATIVE() {
    if(position<sizes[TENTATIVE]) {

             int i=position+1;
             while(tent_buttons[i].state==DISABLED){
                 i++;
             }
             if(i<sizes[TENTATIVE]){
                 handleOut(tent_buttons, position, sizes[TENTATIVE]);
                 position=i;
                 handleIn(tent_buttons, position, sizes[TENTATIVE]);
         }
    }
}

/**
 * @brief manages the choice of tentative trough the pressure of the button (except to prev and next)
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handlePressure_TENTATIVE() {
    if (position!=0) {
        game.tentatives=atoi((char*)tent_buttons[position].text.string);
    }
    else {
        game.tentatives=0;
    }
    handleSelection(tent_buttons);
}

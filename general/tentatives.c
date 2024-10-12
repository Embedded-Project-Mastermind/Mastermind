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
    Graphics_Button other_things[]={
        {DISABLED, {TENT_DIM+1, 32+2, TENT_DIM*4-1, 32+TENT_DIM-1}, {"NO TENT", false}},
        {DISABLED, {1, 32+2, TENT_DIM-1, 32+TENT_DIM-1}, {"", false}}
    };
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

void fn_TENTATIVE(void) {
    reset_Screen();
    //DRAW FUNCTION
    reset_Screen();
    initArray(tent_buttons, sizes[TENTATIVE]);
    defaultDraw();
    drawTentatives(sizes[TENTATIVE]);
    //FOLLOWING POSITION
}
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
void handlePressure_TENTATIVE() {
    game.tentatives=atoi((char*)tent_buttons[position].text.string);
    handleSelection(tent_buttons);
}

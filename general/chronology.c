/*
 * chronologyEs.c
 *
 *  Created on: 31 ott 2024
 *      Author: niccolocristoforetti
 */
#include "chronology.h"
#include "implementations.h"
#include "graphics.h"
#include "fsm.h"


/***************************************
*
* drawChronology() - function that create
* buttons and text for the Chronology screen
* no input
* no output
*
***************************************/

void drawChronology(void) {
    Graphics_Button return_to={STANDARD, {128-16+1, 1, 128-1, 16-1}, {"->", false}};
    int i;
    for (i=0; i<sizes[CHRONOLOGY]; i++) {
        drawButton(chronology_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(chronology_buttons, sizes[CHRONOLOGY]));
    }
    for (i=0; i<2; i++) {
        drawButton(other_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(other_buttons, 2));
    }
    drawButton(return_to, GRAPHICS_COLOR_CYAN, STANDARD, findSelected(&return_to, 1));
}

/***************************************
*
* fn_CHRONOLOGY() - functions that create
* the Chronology screen starting from
* resetting the previous screen
* no input
* no output
*
***************************************/


void fn_CHRONOLOGY(void) {
    reset_Screen();
    //DRAW FUNCTION
    reset_Screen();
    chronology_buttons[position].state=FOCUSED;
    defaultDraw();
    drawChronology();
    //FOLLOWING POSITION
    //OTHER_BUTTONS COLOR
    if(game.count_tent-1>=3){
        other_buttons[1].state=SELECTED;
    }
}

/***************************************
*
* upStick_CHRONOLOGY() / douwnStick_CHRONOLOGY() / rightStick_CHRONOLOGY()
* they manage what to do when the user
* moves the stick
* no input
* no output
*
***************************************/

void upStick_CHRONOLOGY() {
    if(position!=0) {
        handleOut(chronology_buttons, position, sizes[CHRONOLOGY]);
        position=0;
        handleIn(chronology_buttons, position, sizes[CHRONOLOGY]);
    }
    else if(other_buttons[0].state==SELECTED){

    }
}
void downStick_CHRONOLOGY() {
    /*if(position==0) {
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
    }*/
}
void rightStick_CHRONOLOGY() {/*
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
    }*/
}

/*
 * chronology.c
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
        drawButton(tent_number[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(chronology_buttons, sizes[CHRONOLOGY]));
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
    pos=0;
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
    updatePos();
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
        position--;
        handleIn(chronology_buttons, position, sizes[CHRONOLOGY]);
    }
    else if(pos>0){
        pos--;
        if(pos==0){
            other_buttons[0].state=DISABLED;
        }
        //Modifica le schermate precedenti
        updatePos();

    }
}
void downStick_CHRONOLOGY() {
    if(position!=2) {
        handleOut(chronology_buttons, position, sizes[CHRONOLOGY]);
        position++;
        handleIn(chronology_buttons, position, sizes[CHRONOLOGY]);
    }
    else if(other_buttons[1].state==SELECTED) {
        pos++;
        if(game.count_tent-1<=pos+sizes[CHRONOLOGY]){
            other_buttons[1].state=DISABLED;
        }
        //Modifica le schermate precedenti
        updatePos();

    }
}
void rightStick_CHRONOLOGY() {
    display_position--;
}
/***************************************
*
* updatePos()
* Update the number of tent for each
* space
* no input
* no output
*
***************************************/

void updatePos(){
    char buffer[sizeof(long)*8+1][2];
    for(i=0; i<sizes[CHRONOLOGY]; i++){
          tent_number[i].text.string=(int8_t*)ltoa((long)game.count_tent-i-pos, buffer[0], 10);
    }
}

/*
 * doubles.c
 *
 *  Created on: 10 Oct 2024
 *      Author: calvo
 */

#include "doubles.h"

void create_doubles_text(void){

    Graphics_setForegroundColor(&grContext, STANDARD_COLOR);
    Graphics_drawStringCentered(&grContext, (int8_t *)doubles_text.string, AUTO_STRING_LENGTH, 40 , 50 , doubles_text.opacity);
    int i, elems= 3;
    for(i=0; i< elems; i++){
        Graphics_drawStringCentered(&grContext, (int8_t *)doubles_description[i].string, AUTO_STRING_LENGTH, 64 , 68+10*i , doubles_description[i].opacity);
    }
    Graphics_setForegroundColor(&grContext, FILL_UPPER_RECT);


}

void create_doubles_buttons(void){
    int i, elems= 3;
    for(i=0; i<elems; i++){
        if(i<elems-2){drawButton(doubles_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(doubles_buttons, sizes[DOUBLES]));}
        else{drawButton(doubles_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(doubles_buttons, sizes[DOUBLES]));}
    }

}

void change_screen_d(void){
    defaultDraw();
    create_doubles_text();
    create_doubles_buttons();
}

void fn_DOUBLES(void) {
    reset_Screen();
    doubles_buttons[sizes[DOUBLES]-1].state=STANDARD;
    initArray(doubles_buttons, sizes[DOUBLES]);
    change_screen_d();
}

void upStick_DOUBLES(){
    if(position>0){
        handleOut(doubles_buttons, position, sizes[DOUBLES]);
        position=0;
        handleIn(doubles_buttons, position, sizes[DOUBLES]);
    }
}
void downStick_DOUBLES(){
    if(position==0){
        handleOut(doubles_buttons, position, sizes[DOUBLES]);
        position=2;
        handleIn(doubles_buttons, position, sizes[DOUBLES]);
    }
}
void leftStick_DOUBLES(){
    if(position==2){
        handleOut(doubles_buttons, position, sizes[DOUBLES]);
        position--;
        handleIn(doubles_buttons, position, sizes[DOUBLES]);
       }
}
void rightStick_DOUBLES(){
    if(position==1){
        handleOut(doubles_buttons, position, sizes[DOUBLES]);
        position++;
        handleIn(doubles_buttons, position, sizes[DOUBLES]);
       }
}
void handlePressure_DOUBLES() {

}


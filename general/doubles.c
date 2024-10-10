/*
 * doubles.c
 *
 *  Created on: 10 Oct 2024
 *      Author: calvo
 */

#include "doubles.h"

void create_doubles_text(void){

    Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
    Graphics_drawStringCentered(&grContext, (int8_t *)doubles_text.string, AUTO_STRING_LENGTH, 40 , 50 , doubles_text.opacity);
    int i, elems= 3;
    for(i=0; i< elems; i++){
        Graphics_drawStringCentered(&grContext, (int8_t *)doubles_description[i].string, AUTO_STRING_LENGTH, 64 , 68+10*i , doubles_description[i].opacity);
    }
    Graphics_setForegroundColor(&grContext, FILL_UPPER_RECT);


}

void create_doubles_buttons(void){
    doubles_buttons[1]=prevButton;
    doubles_buttons[2]=nextButton;
    int i, elems= 3;
    for(i=0; i<elems; i++){
        if(i<elems-2){drawButton(doubles_buttons[i], STANDARD_COLOR, SELECTED_COLOR);}
        else{drawButton(doubles_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);}
    }

}

void change_screen_d(void){
    defaultDraw();
    create_doubles_text();
    create_doubles_buttons();
}

void fn_DOUBLES(void) {
    change_screen_d();
}

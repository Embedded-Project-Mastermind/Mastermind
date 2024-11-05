/*
 * Title: doubles.h
 * Primary Authors: Daniele Calvo
 * Helpers: Alessandro Benassi
 * Maintainability: Matteo Gottardelli
 * Date Creation: 10 ott 2024
 */

#include "doubles.h"

void create_doubles_text(void){
    Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
    Graphics_drawStringCentered(&grContext, (int8_t *)doubles_text.string, AUTO_STRING_LENGTH, 40 , 47 , doubles_text.opacity);
    int i, elems= 3;
    for(i=0; i< elems; i++){
        Graphics_drawStringCentered(&grContext, (int8_t *)doubles_description[i].string, AUTO_STRING_LENGTH, 65 , 68+10*i , doubles_description[i].opacity);
    }
}

void create_doubles_buttons(void){
    int i, elems= 3;
    for(i=0; i<elems; i++){
        if(i<elems-2){
            drawButton(doubles_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(doubles_buttons, sizes[DOUBLES]));
        }
        else{
            drawButton(doubles_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(doubles_buttons, sizes[DOUBLES]));
        }
    }

}

void change_screen_d(void){
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
    rectangleWithText((Graphics_Rectangle){1, 34, 126, 59}, DISABLED_COLOR, (Graphics_Text){{""}, false}, STANDARD_COLOR);
    rectangleWithText((Graphics_Rectangle){1, 61, 126, 95}, STANDARD_COLOR, (Graphics_Text){{""}, false}, STANDARD_COLOR);
    create_doubles_text();
    create_doubles_buttons();
}

void fn_DOUBLES(void) {
    reset_Screen();
    initArray(doubles_buttons, sizes[DOUBLES]);
    if (doubles_buttons[sizes[DOUBLES]-1].state==DISABLED) {
        doubles_buttons[sizes[DOUBLES]-1].state=STANDARD;
    }
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
    if (doubles_buttons[0].state == SELECTED) {
        game.doubles=false;
        doubles_buttons[0].text.string="No";
        handleDeselection(doubles_buttons);
    } else {
        game.doubles=true;
        doubles_buttons[0].text.string="Yes";
        handleSelection(doubles_buttons);
    }
}



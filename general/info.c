/*
 * info.c
 *
 *  Created on: 10 Oct 2024
 *      Author: calvo
 */

#include "info.h"

void change_screen_i(void){
    defaultDraw();
    char buffer[sizeof(long)*8+1][2];
    int8_t str[2]={game.difficulty,'\0'};
    info_texts_results[1].string= (int8_t*)ltoa((long)game.dim, buffer[0], 10);
    info_texts_results[2].string= str;
    info_texts_results[3].string= (game.doubles) ? (int8_t*)"Yes" : (int8_t*)"No";
    if(game.tentatives!=0) {
        info_texts_results[4].string= (int8_t*)ltoa((long)game.tentatives, buffer[1], 10);
    }
    else {
        info_texts_results[4].string=(int8_t*)"No";
    }

    Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_BLACK);
       int i, elems= 5;
       for(i=1; i< elems; i++){ printf("%s", info_texts[i].string); fflush(stdout); Graphics_drawString(&grContext, (int8_t *)info_texts[i].string, AUTO_STRING_LENGTH, 10 , 40+10*(i-1) , info_texts[i].opacity);}
       for(i=1; i< elems; i++){ Graphics_drawString(&grContext, (int8_t *)info_texts_results[i].string, AUTO_STRING_LENGTH, 90 , 40+10*(i-1) , info_texts_results[i].opacity);}
    Graphics_setForegroundColor(&grContext, FILL_UPPER_RECT);

    for(i=0; i<2; i++){drawButton(info_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, position);}
}
void fn_INFO(void) {
    reset_Screen();
    initArray(info_buttons, sizes[INFO]);
    if (info_buttons[sizes[INFO]-1].state==DISABLED) {
       info_buttons[sizes[INFO]-1].state=STANDARD;
    }
    change_screen_i();
}

void upStick_INFO(){

}
void downStick_INFO(){

}
void leftStick_INFO(){
    if(position==1){
        handleOut(info_buttons, position, sizes[INFO]);
        position--;
        handleIn(info_buttons, position, sizes[INFO]);
       }
}
void rightStick_INFO(){
    if(position==0){
        handleOut(info_buttons, position, sizes[INFO]);
        position++;
        handleIn(info_buttons, position, sizes[INFO]);
       }
}
void handlePressure_INFO() {
    handleSelection(info_buttons);
}


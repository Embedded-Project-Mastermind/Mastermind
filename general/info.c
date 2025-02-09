/*
 * Title: info.c
 * Primary Authors: Daniele Calvo
 * Helpers: Matteo Gottardelli
 * Maintainability: Matteo Gottardelli
 * Date Creation: 5 ott 2024
 */

#include "info.h"

/**
 * @brief manages how to set all info's interface, also calling the functions to create the texts and the buttons
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void change_screen_i(void){
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
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
/**
 * @brief calls all needed
 * functions to change the previous interface
 * with the one of the doubles' state
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void fn_INFO(void) {
    reset_Screen();
    initArray(info_buttons, sizes[INFO]);
    if (info_buttons[sizes[INFO]-1].state==DISABLED) {
       info_buttons[sizes[INFO]-1].state=STANDARD;
    }
    change_screen_i();
}
/**
 * @brief manage what to do when the user moves the stick up
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void upStick_INFO(){}
/**
 * @brief manage what to do when the user moves the stick down
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void downStick_INFO(){}
/**
 * @brief manage what to do when the user moves the stick left
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void leftStick_INFO(){
    if(position==1){
        handleOut(info_buttons, position, sizes[INFO]);
        position--;
        handleIn(info_buttons, position, sizes[INFO]);
       }
}
/**
 * @brief manage what to do when the user moves the stick right
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void rightStick_INFO(){
    if(position==0){
        handleOut(info_buttons, position, sizes[INFO]);
        position++;
        handleIn(info_buttons, position, sizes[INFO]);
       }
}
/**
 * @brief calls the function for the "back" and "next" button's handle
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void handlePressure_INFO() {
    handleSelection(info_buttons);
}


/*
 * info.c
 *
 *  Created on: 10 Oct 2024
 *      Author: calvo
 */

#include "info.h"

void change_screen_i(void){
    defaultDraw();

    info_buttons[0]=prevButton;
    info_buttons[1]=nextButton;

    char buffer[sizeof(long)*8+1][2];
    game.dim=3;
    game.tentatives=6;
    game.difficulty= 'B';
    info_texts_results[0].string= (int8_t*)ltoa((long)game.dim, buffer[0], 10);
    info_texts_results[1].string= (int8_t)game.difficulty;
    info_texts_results[2].string= (game.doubles) ? (int8_t*)"Yes" : (int8_t*)"No";
    info_texts_results[3].string= (int8_t*)ltoa((long)game.tentatives, buffer[1], 10);

    Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
       int i, elems= 4;
       for(i=0; i< elems; i++){ Graphics_drawString(&grContext, (int8_t *)info_texts[i].string, AUTO_STRING_LENGTH, 10 , 40+10*i , info_texts[i].opacity);}
       for(i=0; i< elems; i++){ Graphics_drawString(&grContext, (int8_t *)info_texts_results[i].string, AUTO_STRING_LENGTH, 90 , 40+10*i , info_texts_results[i].opacity);}
    Graphics_setForegroundColor(&grContext, FILL_UPPER_RECT);

    for(i=0; i<2; i++){drawButton(info_buttons[i], FILL_MOVEMENT, STANDARD_COLOR);}


}



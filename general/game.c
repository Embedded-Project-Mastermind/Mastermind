/*
 * game.c
 *
 *  Created on: 27 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "game.h"

bool configurationGame=false;

void fn_GAME(void) {
    if(!configurationGame) {//TO REMOVE ONLY FOR EXAMPLE
        reset_Screen();
        configurationGame=true;
        defaultDraw();
    }
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void elaborateColor(int8_t c) {
    if(configurationGame) {
        P1->OUT &= ~BIT0;
        P2->OUT = 0;
        switch(c) {
            case 'R': P2->OUT |= (BIT0); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_RED); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'O': P1->OUT |= (BIT0); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_ORANGE); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'Y': P2->OUT |= (BIT0 | BIT1); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_YELLOW);Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'G': P2->OUT |= (BIT1); Graphics_setForegroundColor(&grContext,  GRAPHICS_COLOR_GREEN); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'B': P2->OUT |= (BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_BLUE); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'C': P2->OUT |= (BIT1 | BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_CYAN); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'W': P2->OUT |= (BIT0 | BIT1 | BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_WHITE); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 'P': P2->OUT |= (BIT0 | BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_PINK); Graphics_fillCircle(&grContext, 64, 64, 32); break;
        }
        interruptFlag=true;
    }
}

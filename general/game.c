/*
 * game.c
 *
 *  Created on: 27 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "game.h"
#include "gamelogic2.h"

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

void elaborateColor(int16_t c) {
    if(configurationGame) {
        P1->OUT &= ~BIT0;
        P2->OUT = 0;
        color_selected=c;
        switch(c) {
            case 1: P2->OUT |= (BIT0); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_RED); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 7: P1->OUT |= (BIT0); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_ORANGE); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 4: P2->OUT |= (BIT0 | BIT1); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_YELLOW);Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 2: P2->OUT |= (BIT1); Graphics_setForegroundColor(&grContext,  GRAPHICS_COLOR_GREEN); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 3: P2->OUT |= (BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_BLUE); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 6: P2->OUT |= (BIT1 | BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_CYAN); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 8: P2->OUT |= (BIT0 | BIT1 | BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_WHITE); Graphics_fillCircle(&grContext, 64, 64, 32); break;
            case 5: P2->OUT |= (BIT0 | BIT2); Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_PINK); Graphics_fillCircle(&grContext, 64, 64, 32); break;
        }
        current_state=INSERT_COLOR;
        interruptFlag=true;
    }
}


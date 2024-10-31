/*
 * game.c
 *
 *  Created on: 27 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "game.h"
#include "gamelogic2.h"
#include "gamelogic1.h"

bool configurationGame=false;

void fn_GAME(void) {
    if(!configurationGame) {//TO REMOVE ONLY FOR EXAMPLE
        initGame(5, 'A', true, 7); //REMOVE WHEN CONNECTED TO ALL
        configurationGame=true;
        initCircles();

    }
    reset_Screen();
    //DRAW FUNCTION
    Graphics_Rectangle temp={1, 34, 126, 108};
    Graphics_drawRectangle(&grContext, &temp);
    Graphics_setForegroundColor(&grContext, STANDARD_COLOR);
    Graphics_fillRectangle(&grContext, &temp);
    defaultDraw();
    drawCircles();
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
void initCircles() {
    switch(game.dim) {
        case 3: populateCircles(25, 13); break;
        case 4: populateCircles(20, 10); break;
        case 5: populateCircles(15, 9); break;
        case 6: populateCircles(0, 0); break;
        default: exit(1);
    }
}
void populateCircles(int16_t offset, int16_t radius){
    for (i=0; i<game.dim; i++) {
            circles[i].y=56;
            circles[i].radius=radius;
            if(game.dim<=4) {
                circles[i].x=offset+radius*3*i;//offset
            }
            else {
                circles[i].x=offset+radius*2*i+radius*2/3*i;//offset
            }
            circles[i].color=STANDARD_COLOR;
    }
}
void drawCircles() {
    for (i=0; i<game.dim; i++) {
        Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
        Graphics_drawCircle(&grContext, circles[i].x, circles[i].y, circles[i].radius);
        if(circles[i].color!=STANDARD_COLOR) {
            Graphics_setForegroundColor(&grContext, circles[i].color);
            Graphics_fillCircle(&grContext, circles[i].x, circles[i].y, circles[i].radius);
        }
    }
}



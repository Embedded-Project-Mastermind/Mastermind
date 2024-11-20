/*
 * Title: game.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Alessandro Benassi, Matteo Gottardelli
 * Date Creation: 31 ott 2024
 */
#include "game.h"
#include "gamelogic1.h"
#include "joystick.h"

bool configurationGame=false;
Graphics_Rectangle textRect={1, 70, 126, 106};

void fn_GAME(void) {
    if(!configurationGame) {//TO REMOVE ONLY FOR EXAMPLE
       // initGame(3, 'A', true, 7); //REMOVE WHEN CONNECTED TO ALL
        configurationGame=true;
        initCircles();
    }
    reset_Screen();
    //DRAW FUNCTION
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
    rectangleWithText((Graphics_Rectangle){1, 34, 126, 108}, STANDARD_COLOR, (Graphics_Text){{""}, false}, STANDARD_COLOR);
    drawCircles(circles);
    if (game.count_tent==0){
        rectangleWithText((Graphics_Rectangle){0, 110, 128, 128}, DISABLED_COLOR, (Graphics_Text){{"<- CHRONOLOGY"}, false}, STANDARD_COLOR);
    }
    else {
        rectangleWithText((Graphics_Rectangle){0, 110, 128, 128}, FILL_MOVEMENT, (Graphics_Text){{"<- CHRONOLOGY"}, false}, STANDARD_COLOR);
    }
}
void elaborateColor(int16_t c) {
    if(configurationGame) {
        if (game.dim!=tentative.count) {
            P1->OUT &= ~BIT0;
            P2->OUT = 0;
            color_selected=c;
            switch(c) {
                case 1: P2->OUT |= (BIT0); break;
                case 7: P1->OUT |= (BIT0); break;
                case 4: P2->OUT |= (BIT0 | BIT1); break;
                case 2: P2->OUT |= (BIT1); break;
                case 3: P2->OUT |= (BIT2); break;
                case 6: P2->OUT |= (BIT1 | BIT2); break;
                case 8: P2->OUT |= (BIT0 | BIT1 | BIT2);  break;
                case 5: P2->OUT |= (BIT0 | BIT2); break;
                default: exit(1);
            }
            current_state=INSERT_COLOR;
            interruptFlag=true;
        }
        else {
            rectangleWithText(textRect,STANDARD_COLOR, (Graphics_Text){{"FULL"}, false}, SELECTED_COLOR);
            interruptFlag=false;
        }
    }
}
void initCircles() {
    switch(game.dim) {
        case 3: populateCircles(25, 13, 56); break;
        case 4: populateCircles(20, 10, 56); break;
        case 5: populateCircles(15, 9, 56); break;
        case 6: populateCircles(11, 8, 56); break;
        default: exit(1);
    }
}
void populateCircles(int16_t offset, int16_t radius, int16_t value_y){
    int i;
    for (i=0; i<game.dim; i++) {
            circles[i].y=value_y;
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
void drawCircles(Graphics_Circle* circs) {
    int k;
    for (k=0; k<game.dim; k++) {
        Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
        Graphics_drawCircle(&grContext, circs[k].x, circs[k].y, circs[k].radius);
        if(circs[k].color!=STANDARD_COLOR) {
            Graphics_setForegroundColor(&grContext, circs[k].color);
            Graphics_fillCircle(&grContext, circs[k].x, circs[k].y, circs[k].radius);
        }
    }
}

void leftStick_GAME() {
    if (game.count_tent!=0){
        display_position++;
        configurationGame=false;
        delay_ms(100);
    }
}
int32_t selectColor(int16_t color) {
    int32_t c;
    switch(color) {
        case 1: c=GRAPHICS_COLOR_RED; break;
        case 2: c=GRAPHICS_COLOR_GREEN; break;
        case 3: c=GRAPHICS_COLOR_BLUE; break;
        case 4: c=GRAPHICS_COLOR_YELLOW; break;
        case 5: c=GRAPHICS_COLOR_PINK; break;
        case 6: c=GRAPHICS_COLOR_CYAN; break;
        case 7: c=GRAPHICS_COLOR_ORANGE; break;
        case 8: c=GRAPHICS_COLOR_WHITE; break;
        default: exit(1);
    }
    return c;
}
void displayResultsOnScreen() {
    for (i=0; i<game.dim; i++) {
        Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
        Graphics_fillCircle(&grContext, circles[i].x, circles[i].y+YLEVEL_OFFSET, circles[i].radius);
        int8_t str[2]={tentative.sol_user[i], '\0'};
        Graphics_setFont(&grContext, &g_sFontCm20);
        rectangleWithText(
            (Graphics_Rectangle){
                circles[i].x - circles[i].radius,
                circles[i].y - circles[i].radius + YLEVEL_OFFSET,
                circles[i].x + circles[i].radius,
                circles[i].y + circles[i].radius + YLEVEL_OFFSET
            },
            -1,
            (Graphics_Text){str, false},
            STANDARD_COLOR
        );
        Graphics_setFont(&grContext, &g_sFontFixed6x8);
        delay_ms(500);
    }
    delay_ms(1000);
}

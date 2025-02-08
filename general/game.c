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

/**
 * @brief Implicit Call that is invoked when we arrive at GAME state in GUI FSM and primarly draw the static elements and dynamic ones
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
 */
void fn_GAME(void) {
    if(!configurationGame) {//TO REMOVE ONLY FOR EXAMPLE
       // initGame(3, 'A', true, 7); //REMOVE WHEN CONNECTED TO ALL
        configurationGame=true;
        initCircles();
    }
    reset_Screen();
    //DRAW FUNCTION
    //rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
    char buffer[sizeof(long)*8+1][2];
    char tentative_text[10]= "";
    strcat(tentative_text,(char*)ltoa((long)(game.count_tent+1), buffer[0], 10));
    if(game.tentatives!=0) {
        strcat(tentative_text," of ");
        strcat(tentative_text,(char*)ltoa((long)game.tentatives, buffer[1], 10));
    }
    rectangleWithText((Graphics_Rectangle){0, 0, 77, 32}, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
    rectangleWithText((Graphics_Rectangle){79, 0, 128, 16}, FILL_UPPER_RECT, (Graphics_Text){"Attempt",false}, SELECTED_COLOR);
    rectangleWithText((Graphics_Rectangle){79, 16, 128, 32}, FILL_UPPER_RECT, (Graphics_Text){(int8_t*)tentative_text,false}, SELECTED_COLOR);//
    rectangleWithText((Graphics_Rectangle){1, 34, 126, 108}, STANDARD_COLOR, (Graphics_Text){{""}, false}, STANDARD_COLOR);
    drawCircles(circles);
    if (game.count_tent==0){
        rectangleWithText((Graphics_Rectangle){0, 110, 128, 128}, DISABLED_COLOR, (Graphics_Text){{"<- CHRONOLOGY"}, false}, STANDARD_COLOR);
    }
    else {
        rectangleWithText((Graphics_Rectangle){0, 110, 128, 128}, FILL_MOVEMENT, (Graphics_Text){{"<- CHRONOLOGY"}, false}, STANDARD_COLOR);
    }
}
/**
 * @brief According to the inputed color, the leds are turned on according to that color (ORANGE case it will be P1.0, for the others will be a direct correspondes to combination of P2.0, P2.1, P2.2
 * @param c Consist in an integer denoting a custom coding of colors (more clarity in input.c)
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
 */
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
/**
 * @brief According to the dimension selected in GUI menu, are preallocated empty circles that change dynamically position and size according to the number, because they have to fit on the screen
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
 */
void initCircles() {
    switch(game.dim) {
        case 3: populateCircles(25, 13, 56); break;
        case 4: populateCircles(20, 10, 56); break;
        case 5: populateCircles(15, 9, 56); break;
        case 6: populateCircles(11, 8, 56); break;
        default: exit(1);
    }
}
/**
 * @brief Initialization effective of the circles according to the inputed parameters
 * @param offset Determine the distance from the leftest pixel of the leftest circle and the left border
 * @param radius Circle radius, distance from the center to the circle border
 * @param value_y Position of y axis according to the screen
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
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
/**
 * @brief Management and color of the circles on screen
 * @param circs The circle initialized array that handles the handle the color of each element in the array
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
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
/**
 * @brief Action that the menu performs when the stick goes left, primarly changing selection and imposing logic visual limits
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
void leftStick_GAME() {
    if (game.count_tent!=0){
        display_position++;
        configurationGame=false;
        delay_ms(100);
    }
}
/**
 * @brief Action that the menu performs when the stick goes left, primarly changing selection and imposing logic visual limits
 * @param color Graphics color definition according to the integer inputed and according to that the circle will be colored
 * @return int32, returns the graphics color in order to color the circle
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
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
/**
 * @brief Effective function that refresh the status of GAME Section, when an update happen
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
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

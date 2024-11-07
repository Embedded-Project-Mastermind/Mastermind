/*
 * Title: chronology.h
 * Primary Authors: NiccolÃ² Cristoforetti
 * Helpers: Matteo Gottardelli
 * Maintainability: NiccolÃ² Cristoforetti, Matteo Gottardelli
 * Date Creation: 31 ott 2024
 */
#include "chronology.h"
#include "implementations.h"
#include "graphics.h"
#include "fsm.h"
#include "joystick.h"
#include "game.h"
#include "gamelogic1.h"
#include "string.h"

/***************************************
*
* drawChronology() - function that create
* buttons and text for the Chronology screen
* no input
* no output
*
***************************************/

void drawChronology(void) {
    Graphics_Button return_to={STANDARD, {128-16+1, 1, 128-1, 16-1}, {"->", false}};
    int i;
    for (i=0; i<sizes[CHRONOLOGY]; i++) {
        drawButton(chronology[i].button, STANDARD_COLOR, SELECTED_COLOR, -1);
        rectangleWithText(chronology[i].num_rect, SELECTED_COLOR, chronology[i].num, STANDARD_COLOR);
        if(chronology[i].button.state!=DISABLED){
            drawCircles(chronology[i].chrono_circles);
        }
    }
    for (i=0; i<2; i++) {
        drawButton(other_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, -1);
    }
    drawButton(return_to, GRAPHICS_COLOR_CYAN, STANDARD, findSelected(&return_to, 1));
}

/***************************************
*
* fn_CHRONOLOGY() - functions that create
* the Chronology screen starting from
* resetting the previous screen
* no input
* no output
*
***************************************/


void fn_CHRONOLOGY(void) {
    //DRAW FUNCTION
    reset_Screen();
    if(game.count_tent-1>=3){
        other_buttons[1].state=STANDARD;
    }
    for (i=0; i<sizes[CHRONOLOGY] && i<game.count_tent; i++) {
          chronology[i].button.state=STANDARD;
    }
    chronology[position].button.state=FOCUSED;
    rectangleWithText((Graphics_Rectangle){upperRect.xMin, upperRect.yMin, upperRect.xMax, upperRect.yMax-16}, FILL_UPPER_RECT, labelText, SELECTED_COLOR);

    updatePos();
    drawChronology();

}


int16_t char_Conversion_to_Int(int8_t index) {
    int16_t c=0;
    switch (index) {
        case 'R': c = 1; break; // Red
        case 'G': c = 2; break; // Green
        case 'B': c = 3; break; // Blue
        case 'Y': c = 4; break; // Yellow
        case 'P': c = 5; break; // Purple
        case 'C': c = 6; break; // Cyan
        case 'O': c = 7; break; // Orange
        case 'W': c = 8; break; //White
        default: exit(1); // Exit on error
    }
    return c; // Return the character representation
}

void populateChronologyCircles(int16_t offset, int16_t radius, int16_t value, int16_t index){
    for (i=0; i<game.dim; i++) {
        chronology[value].chrono_circles[i].radius=radius;
        if(i<3){
            chronology[value].chrono_circles[i].x= offset+(58/3)*(i+1);
            chronology[value].chrono_circles[i].y=32*value+35;
        } else {
            chronology[value].chrono_circles[i].x= offset+(58/3)*(i-2);
                        chronology[value].chrono_circles[i].y=32*value+45;
        }

        int16_t tmp = char_Conversion_to_Int(game.chronology[index*game.dim*2+i]);
        chronology[value].chrono_circles[i].color=selectColor(tmp);
    }
}


/***************************************
*
* upStick_CHRONOLOGY() / douwnStick_CHRONOLOGY() / rightStick_CHRONOLOGY()
* they manage what to do when the user
* moves the stick
* no input
* no output
*
***************************************/

void upStick_CHRONOLOGY() {
    if(position!=0) {
        chronology[position].button.state=STANDARD;
        position--;
        chronology[position].button.state=FOCUSED;
    }
    else if(position==0 && other_buttons[0].state==STANDARD){
        pos_chronology--;
        position=0;
        if(pos_chronology==0){
            other_buttons[0].state=DISABLED;
        }
        if(game.count_tent-1>pos_chronology+sizes[CHRONOLOGY]){
            other_buttons[1].state=STANDARD;
        }
        //Modifica le schermate precedenti
        updatePos();
    }
}
void downStick_CHRONOLOGY() {
    if(position+1<game.count_tent && position!=sizes[CHRONOLOGY]) {
        chronology[position].button.state=STANDARD;
        position++;
        chronology[position].button.state=FOCUSED;
    }
    else if(position==sizes[CHRONOLOGY]-1 && other_buttons[1].state==STANDARD) {
        pos_chronology++;
        position=sizes[CHRONOLOGY]-1;
        if(game.count_tent-1<=pos_chronology+sizes[CHRONOLOGY]){
            other_buttons[1].state=DISABLED;
        }
        if(pos_chronology>0) {
            other_buttons[0].state=STANDARD;
        }
        //Modifica le schermate precedenti
        updatePos();
    }
}
void rightStick_CHRONOLOGY() {
    display_position--;
    configurationGame=true;
    delay_ms(100);
}
/***************************************
*
* updatePos()
* they manage what to do when the user
* moves the stick
* no input
* no output
*
***************************************/

void updatePos(){
        for (i=0; i<sizes[CHRONOLOGY]; i++){
            if (chronology[i].button.state!=DISABLED) {
                int16_t result=game.count_tent-i-pos_chronology;
                if(result>0) {
                    populateChronologyCircles(BASIC_OFFSET,RADIUS,i, result-1);
                    char buffer[20];
                    char* str=ltoa((long)result, buffer, 10);
                    chronology[i].num.string = (int8_t*)malloc(strlen(str) + 1);
                    if (chronology[i].num.string == NULL) {
                        printf("Memory allocation failed!\n");
                        emergency();

                        exit(1);
                    }
                    for (j=0; str[j]!='\0'; j++){
                        chronology[i].num.string[j] = (int8_t)str[j];
                    }
                    chronology[i].num.string[strlen(str)] = '\0';

                    printf("Chronology[%d] num.string: %s %s\n", i, str, chronology[i].num.string);
                }
            }
        }
}

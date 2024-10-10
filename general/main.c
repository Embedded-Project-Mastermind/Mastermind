/*
 * fsm.h
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "stdio.h"
#include "implementations.h"
#include "graphics.h"
#include "fsm.h"

typedef struct Graphics_StateMachine {
    Graphics_State state; //Current Graphics State
    void (*state_function)(void); //Pointer to that state function
} Graphics_StateMachine;

Graphics_StateMachine gfsm[]={
     {START_GR, fn_START_GR},
     {DIMENSION, fn_DIMENSION},
     {DIFFICULTY, fn_DIFFICULTY},
     {TENTATIVE, fn_TENTATIVE},
     {DOUBLES, fn_DOUBLES},
     {INFO, fn_INFO},
     {GAME, fn_GAME},
     {CHRONOLOGY, fn_CHRONOLOGY},
     {END, fn_END}
};
Game game;
Tentative tentative;
State current_state=START;
Graphics_State display_position=DIMENSION;
Graphics_Rectangle upperRect={0, 0, 128, 32};
Graphics_Button prevButton={STANDARD, {0, 97, 63, 128}, {{"Back"}, false}};
Graphics_Button nextButton={DISABLED, {65, 97, 128, 128}, {{"Next"}, false}};
uint8_t position=0;
Graphics_Text labelText={"", false};

void labelDefining(Graphics_State pos) {
    switch(pos) {
        case START_GR: labelText.string=""; break;
        case DIMENSION: labelText.string="SELECT DIMENSION"; break;
        case DIFFICULTY:labelText.string="SELECT DIFFICULTY"; break;
        case TENTATIVE: labelText.string="NUMBER OF TRIES"; break;
        case DOUBLES: labelText.string="DOUBLE PRESENCE"; break;
        case INFO: labelText.string="SUMMARY"; break;
        case GAME:  labelText.string=""; break;
        case CHRONOLOGY: labelText.string=""; break;
        case END: labelText.string=""; break;
        default: exit(1);
    }

}

int main(void) {
    WDT_A_holdTimer();
    hardware_Init();
    while(1) {
       if(display_position<ERROR_GR) {
           labelDefining(display_position);
           (*gfsm[display_position].state_function)();
       }
       else {
           return 0;
       }
        __sleep();
    }

}

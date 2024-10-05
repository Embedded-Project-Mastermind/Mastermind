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
Graphics_State display_position=START_GR;

int main(void) {
    WDT_A_holdTimer();
    hardware_Init();
    while(1) {
       if(display_position<ERROR_GR) {
           (*gfsm[display_position].state_function)();
       }
       else {
           return 0;
       }
    }
}

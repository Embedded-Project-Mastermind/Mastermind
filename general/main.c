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
#include "dimension.h"
#include "tentatives.h"
#include "joystick.h"

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

//Alessandro Benassi's code
Graphics_Button dim_buttons[]={
    {FOCUSED, {0, 34, 63, 63 }, {"3", false}},
    {STANDARD, {65, 34, 128, 63}, {"4", false}},
    {STANDARD, {0, 65, 63, 96}, {"5", false}},
    {STANDARD, {65, 65, 128, 96}, {"6", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}}
};

//Niccolò Cristoforetti's code
Graphics_Button tent_buttons[]={
    {STANDARD, {1, 32+2, TENT_DIM-1, 32+TENT_DIM-1}, {"", false}},
    {FOCUSED, {TENT_DIM/4+1, 32+TENT_DIM/4+1, TENT_DIM/2+TENT_DIM/4-1, 32+TENT_DIM/2+TENT_DIM/4-1}, {"", false}},
    {DISABLED, {TENT_DIM+1, 32+2, TENT_DIM*4-1, 32+TENT_DIM-1}, {"NO TENT", false}},
    {STANDARD, {1, 32+TENT_DIM+1, TENT_DIM-1, 32+TENT_DIM*2-1}, {"3", false}},
    {STANDARD, {TENT_DIM+1, 32+TENT_DIM+1, TENT_DIM*2-1, 32+TENT_DIM*2-1}, {"5", false}},
    {STANDARD, {TENT_DIM*2+1, 32+TENT_DIM+1, TENT_DIM*3-1, 32+TENT_DIM*2-1}, {"7", false}},
    {STANDARD, {TENT_DIM*3+1, 32+TENT_DIM+1, TENT_DIM*4-1, 32+TENT_DIM*2-1}, {"10", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}}
};

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
void ADC14_IRQHandler(void)
{
    uint64_t status;
    int i;
    status = ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);

    /* ADC_MEM1 conversion completed */
    if(status & ADC_INT1)
    {
        /* Store ADC14 conversion results */
        resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
        resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
        uint16_t x=resultsBuffer[0];
        uint16_t y=resultsBuffer[1];

        NavigateMenu(findDirection(x, y));
        for (i=0; i<100000; i++);
    }
}

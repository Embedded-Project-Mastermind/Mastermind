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
#include "start.h"
#include "dimension.h"
#include "tentatives.h"
#include "doubles.h"
#include "difficulty.h"
#include "info.h"
#include "joystick.h"
#include "buttons.h"

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
Graphics_State display_position=DIFFICULTY;
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
//Matteo Gottardelli's code
Graphics_Button diff_buttons[]={
    {FOCUSED, {1, 32+2, DIFF_DIM, 32+DIFF_DIM}, {"A", false}},
    {STANDARD, {1, 32+DIFF_DIM+2, DIFF_DIM, 32+2*DIFF_DIM+1}, {"B", false}},
    {STANDARD, {1, 96-DIFF_DIM-1, DIFF_DIM, 96-2}, {"C", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}}
};
Graphics_Text explain[][DIFF_TYPES]={
     {{"EASY MODE", false},{"MEDIUM MODE", false}, {"HARD MODE", false}, {"", false}},
     {{"INFO PER COLOR", false},{"INFO GENERAL", false},{"INFO GENERAL", false}, {"", false}},
     {{"- RIGHT POS", false},{"- RIGHT POS", false},{"- RIGHT POS", false}, {"", false}},
     {{"- WRONG POS", false}, {"- WRONG POS", false}, {"", false}, {"", false}}
};
//Niccolò Cristoforetti's code
Graphics_Button tent_buttons[]={
    {FOCUSED, {TENT_DIM/4+1, 32+TENT_DIM/4+1, TENT_DIM/2+TENT_DIM/4-1, 32+TENT_DIM/2+TENT_DIM/4-1}, {"", false}},
    {STANDARD, {1, 32+TENT_DIM+1, TENT_DIM-1, 32+TENT_DIM*2-1}, {"3", false}},
    {STANDARD, {TENT_DIM+1, 32+TENT_DIM+1, TENT_DIM*2-1, 32+TENT_DIM*2-1}, {"5", false}},
    {STANDARD, {TENT_DIM*2+1, 32+TENT_DIM+1, TENT_DIM*3-1, 32+TENT_DIM*2-1}, {"7", false}},
    {STANDARD, {TENT_DIM*3+1, 32+TENT_DIM+1, TENT_DIM*4-1, 32+TENT_DIM*2-1}, {"10", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}}
};
Graphics_Button text_no_tent={DISABLED, {TENT_DIM+1, 32+2, TENT_DIM*4-1, 32+TENT_DIM-1}, {"NO TENT", false}};
Graphics_Button start_button={FOCUSED, {32, 96, 96, 112}, {"START", false}};
//Daniele Calvo's code
Graphics_Text doubles_text={{"Doubles"}, false};  //DOUBLE state part
Graphics_Text doubles_description[]={ 
    {{"Possibility of "}, false},
    {{"the same color "}, false},
    {{"repeated or not"}, false}};
Graphics_Button doubles_buttons[]={ 
    {FOCUSED, {80, 40, 110, 60}, {{"No"}, false}},
    {STANDARD, {0,0,0,0}, {{""}, false}},
    {STANDARD, {0,0,0,0}, {{""}, false}}};
   
Graphics_Text info_texts[]={                     //INFO sate part
    {{"Dimension: "}, false},
    {{"Difficulty: "}, false},
    {{"Doubles: "}, false},
    {{"Tentatives: "}, false}};
Graphics_Text info_texts_results[]={ 
    {{" "}, false},
    {{" "}, false},
    {{" "}, false},
    {{" "}, false}};
Graphics_Button info_buttons[]={ 
    {STANDARD, {0,0,0,0}, {{""}, false}},
    {STANDARD, {0,0,0,0}, {{""}, false}}};
//SIZES
int8_t sizes[ERROR_GR];
void setSizes() {
    int i;
    for (i=0; i<ERROR_GR; i++) {
        switch(i) {
            case START_GR: sizes[i]=1; break;
            case DIMENSION: sizes[i]=ARRAY_SIZE(dim_buttons); break;
            case DIFFICULTY: sizes[i]=ARRAY_SIZE(diff_buttons); break;
            case TENTATIVE: sizes[i]=ARRAY_SIZE(tent_buttons); break;
            case DOUBLES: sizes[i]=ARRAY_SIZE(doubles_buttons); break;
            case INFO: sizes[i]=ARRAY_SIZE(info_buttons); break;
            case GAME:  sizes[i]=1; break;
            case CHRONOLOGY: sizes[i]=1; break;
            case END: sizes[i]=1; break;
            default: exit(1);
        }
    }
}
//BOOLEANS
bool interruptFlag=false;
bool flagNext=false;
bool flagPrev=false;
int main(void) {
    WDT_A_holdTimer();
    hardware_Init();
    setSizes();
    ADC_EnableInterrupts();
    setupPriorities();
    while(1) {
       interruptFlag=false;
       if(display_position<ERROR_GR) {
           labelDefining(display_position);
           (*gfsm[display_position].state_function)();
       }
       else {
           return 0;
       }
       //__delay_cycles(1000000);
      __enable_irq();
       while(1) {
           ADC_StartConversion(); // Start ADC conversion
           ADC14_toggleConversionTrigger();
           __sleep();
           if (interruptFlag) {
               break;
           }
       }
       __disable_irq();
    }
}

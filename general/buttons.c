/*
 * Title: buttons.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Matteo Gottardelli
 * Date Creation: 11 ott 2024
 */
#include "buttons.h"
#include "msp.h"
#include "graphics.h"
#include "implementations.h"
#include "difficulty.h"
#include "dimension.h"
#include "tentatives.h"
#include "doubles.h"
#include "info.h"
#include "input.h"
#include "game.h"
#include "gamelogic2.h"

void button_Init() {
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5);
    P3->IES |= BIT5;
    P3->IFG &= ~BIT5;
    P3->IE |= BIT5;
    NVIC->ISER[1]|=1<<(PORT5_IRQn & 31);
    P5->IES |= BIT1;
   P5->IFG &= ~BIT1;
   P5->IE |= BIT1;
    NVIC->ISER[1]|=1<<(PORT3_IRQn & 31);
}
void buttonBackAction() {
    if(is_empty()){
        current_state = WAIT;
        rectangleWithText(textRect,STANDARD_COLOR, (Graphics_Text){{"EMPTY"}, false}, SELECTED_COLOR);
        interruptFlag=false;
    }
    else {
        current_state = ELIMINATE_COLOR;
        interruptFlag=true;
    }
}
void buttonConfirmAction() {

    switch(display_position) {
        case START_GR: display_position++; break;
        case DIMENSION: handle_buttons(dim_buttons); break;
        case DIFFICULTY: handle_buttons(diff_buttons); break;
        case TENTATIVE: handle_buttons(tent_buttons); break;
        case DOUBLES: handle_buttons(doubles_buttons); break;
        case INFO: handle_buttons(info_buttons); break;
        case GAME: if(configurationGame){
                //funzione per i bottoni
                if(current_state==WAIT_FULL){
                    current_state = ELABORATE_TENT;
                    interruptFlag=true;
                }
                else {
                    rectangleWithText(textRect,STANDARD_COLOR, (Graphics_Text){{"NOT FULL"}, false}, SELECTED_COLOR);
                    interruptFlag=false;
                }
            } break;
        case CHRONOLOGY: break;
        case END: break;
        //default: exit(1);
    }
    if (display_position!=GAME) {
        interruptFlag=true;
    }

}
void functionPinsDefault(uint8_t status, int8_t port) {
    switching(status, port);
    /*if(!configurationGame) {
      //elaborateOutput();
      //resetArrayInput();
      //interruptFlag=true;
    }*/
    //ADC14_disableConversion();
    //delay_ms(100);
}

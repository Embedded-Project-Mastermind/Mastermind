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

/**
 * @brief Sets up launchpad pins connected for the buttons (P3.5 and P5.1)
 * @return void
 * @author Matteo Gottardelli (Primary Author)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
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
/**
 * @brief Implements back button action that redirects in eliminate colored circle state if there was at least one input, instead outputs that is empty
 * @return void
 * @author Matteo Gottardelli (Primary Author)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
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
/**
 * @brief Implements confirm button action that manage its input according to the state you are in. STARTGR has only one button, so directly redicts; DIMENSION, DIFFICULTY, TENTATIVE, DOUBLES, INFO are menu features and they have their own logic; GAME allows sequence processing only if the sequence is full; CHRONOLOGY and END don't use this button
 * @return void
 * @author Matteo Gottardelli (Primary Author)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
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
/**
 * @brief Deprecated, using switching function, it is only a bridge function now
 * @param status int that represents the current configuration of IFG register, so the flag register that handles interrupts on a port
 * @param port int that represents a port on which an interrupt has occurred
 * @return void
 * @author Matteo Gottardelli (Primary Author)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
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

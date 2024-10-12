/*
 * buttons.c
 *
 *  Created on: 11 ott 2024
 *      Author: matteogottardelligmail.com
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
    //TO IMPLEMENT
}
void buttonConfirmAction() {
    switch(display_position) {
        case START_GR: display_position++; break;
        case DIMENSION: handle_buttons(dim_buttons); break;
        case DIFFICULTY: handle_buttons(diff_buttons); break;
        case TENTATIVE: handle_buttons(tent_buttons); break;
        case DOUBLES: handle_buttons(doubles_buttons); break;
        case INFO: handle_buttons(info_buttons); break;
        case GAME: break;
        case CHRONOLOGY: break;
        case END: break;
        //default: exit(1);
    }

}
void PORT5_IRQHandler(void) {
    if(P5->IFG & BIT1) {
        buttonBackAction();
        P5->IFG &= ~BIT1;
        interruptFlag=true;
        __disable_irq();
        //__delay_cycles(1000000);
    }
}
void PORT3_IRQHandler(void) {
    if(P3->IFG & BIT5) {
        buttonConfirmAction();
        P3->IFG &= ~BIT5;
        interruptFlag=true;
        __disable_irq();
        //__delay_cycles(1000000);
    }
}

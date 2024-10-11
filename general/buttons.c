/*
 * buttons.c
 *
 *  Created on: 11 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "buttons.h"
#include "msp.h"
void button_Init() {
    /* configure P2.0, P2.1 and P2.2 as GPIO */
    P2->SEL0 &= ~(BIT0| BIT1 | BIT2);
    P2->SEL1 &= ~(BIT0| BIT1 | BIT2);

    /* set Port 2.0, 2.1 and 2.2 as output */
    P2->DIR |= (BIT0 | BIT1 | BIT2);

    /* clear the pins */
    P2->OUT &= ~(BIT0| BIT1 | BIT2);
    //P5.1 UPBUTTON (BACK)
    P5->SEL0 &= ~(BIT1);
    P5->SEL1 &= ~(BIT1);
    P5->DIR &= ~BIT1;
    P5->REN |= BIT1;
    P5->OUT |= BIT1;
    P5->IES |= BIT1;
    P5->IFG &= ~BIT1;
    P5->IE |= BIT1;
    //P3.5 DOWNBUTTON (CONFIRM)
    P3->SEL0 &= ~(BIT5);
    P3->SEL1 &= ~(BIT5);
    P3->DIR &= ~BIT5;
    P3->REN |= BIT5;
    P3->OUT |= BIT5;
    P3->IES |= BIT5;
    P3->IFG &= ~BIT5;
    P3->IE |= BIT5;
    NVIC->ISER[1]|=1<<(PORT5_IRQn & 31);
    NVIC->ISER[1]|=1<<(PORT3_IRQn & 31);
}
void PORT5_IRQHandler(void) {
    if(P5->IFG & BIT1) {
        buttonBackAction();
        P5->IFG &= ~BIT1;
        __delay_cycles(200000);
    }
}
void PORT3_IRQHandler(void) {
    if(P3->IFG & BIT5) {
        buttonConfirmAction();
        P5->IFG &= ~BIT5;
        __delay_cycles(200000);
    }
}
void buttonBackAction() {
    P2->OUT ^= BIT0;
}
void buttonConfirmAction() {
    P2->OUT ^= BIT1;
}

/*
 * Title: input.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Matteo Gottardelli
 * Date Creation: 5 ott 2024
 */
#include "input.h"
#include "fsm.h"
#include "buttons.h"
#include "game.h"

// Global variables
bool array[DIMIO];
uint8_t overflow_counter=0;

// Function implementations
void resetArrayInput(void) {
    int i;
    for (i = 0; i < DIMIO; i++) {
        array[i] = false;
    }
}

void setArrayInput(int val) {
    if (val < 0 || val >= DIMIO) {
        resetArrayInput();
    } else {
        array[val] = true;
    }
}

void configurePortsInput(void) {
    //P4.4 ADC, P6.0 ADC, P5.0
    int port;
    P1->DIR &= ~BIT1;
    P1->REN |= BIT1;
    P1->OUT |= BIT1;
    for (port=GPIO_PORT_P3; port<=GPIO_PORT_P6; port++) {
        if (port!=GPIO_PORT_P6 && port!=GPIO_PORT_P5) {
            GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN0);
        }
        if(port!=GPIO_PORT_P4) {//PRESSING joystick
            GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN1);
        }
        GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN2);
        if(port!=GPIO_PORT_P3) {
            GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN3);
        }
        if (port!=GPIO_PORT_P4) {//LEFT DIR
            GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN4);
        }
        GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN5);
        if (port!=GPIO_PORT_P5) {
            GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN6);
        }
        if (port!=GPIO_PORT_P6 && port!=GPIO_PORT_P5) {
            GPIO_setAsInputPinWithPullUpResistor(port, GPIO_PIN7);
        }
    }
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);
    //GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN3);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN4);
    P2->OUT=0;
    //GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN4);
    //GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);
    //GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6); BUZZER
    //GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
}

void configureInterruptPortInput(void) {
    P1->IES = 0xFF;
    P1->IE = 0xFF;
    P1->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT1_IRQn & 31);
    /*P3->IES = 0xFF;
    P3->IE = 0xFF;
    P3->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT3_IRQn & 31);*/
    //P4.4 ADC, P6.0 ADC, P5.0
    P3->IES |= 0x7F;
    P3->IE |= 0x7F;
    P3->IFG =0x80;
    NVIC->ISER[1] |= 1 << (PORT3_IRQn & 31);
    P4->IES = 0xFF;
    P4->IE = 0xFF;
    P4->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT4_IRQn & 31);
    P5->IES = 0x7E;
    P5->IE = 0x7E;
    P5->IFG = 0x81;
    NVIC->ISER[1] |= 1 << (PORT5_IRQn & 31);
    P6->IES = 0xFF;
    P6->IE = 0xFF;
    P6->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT6_IRQn & 31);
}

void triggerPinInterrupt() {
    P1->IFG |= BIT1;
    __NVIC_SetPendingIRQ(PORT1_IRQn);
}

int counterTrue(void) {
    int i, counter = 0;
    for (i = 0; i < DIMIO; i++) {
        if (array[i] == true) {
            counter++;
        }
    }
    return counter;
}

int findTrue(void) {
    int i;
    for (i = 0; i < DIMIO; i++) {
        if (array[i] == true) {
            return i;
        }
    }
    return -1;
}

void elaborateOutput(void) {
    if (counterTrue() == 1) {
        switch (findTrue()) {
           /*case (P1_D*BYTE+0): break; //P1.0
           case (P1_D*BYTE+1): break; //P1.1
           case (P1_D*BYTE+2): break; //P1.2
           case (P1_D*BYTE+3): break; //P1.3
           case (P1_D*BYTE+4): break; //P1.4
           case (P1_D*BYTE+5): break; //P1.5
           case (P1_D*BYTE+6): break; //P1.6
           case (P1_D*BYTE+7): break; //P1.7*/
           //case (P2_D*BYTE+0): break; //P2.0
           //case (P2_D*BYTE+1): break; //P2.1
           //case (P2_D*BYTE+2): break; //P2.2
           //case (P2_D*BYTE+3): break; //P2.3
           //case (P2_D*BYTE+4): break; //P2.4
           //case (P2_D*BYTE+5): break; //P2.5
           //case (P2_D*BYTE+6): break; //P2.6
           //case (P2_D*BYTE+7): break; //P2.7
           case (P3_D*BYTE+0): elaborateColor(1); break; //P3.0
           //case (P3_D*BYTE+1): elaborateColor(1); break; //P3.1
           case (P3_D*BYTE+2): elaborateColor(1); break; //P3.2
           case (P3_D*BYTE+3): elaborateColor(7); break; //P3.3
           case (P3_D*BYTE+4): elaborateColor(7); break; //P3.4
           case (P3_D*BYTE+5): buttonConfirmAction(); break; //P3.5
           case (P3_D*BYTE+6): elaborateColor(4); break; //P3.6
           //case (P3_D*BYTE+7): break; //P3.7
           //case (P4_D*BYTE+0): elaborateColor(4); break; //P4.0
           //case (P4_D*BYTE+1): elaborateColor(4); break; //P4.1
           //case (P4_D*BYTE+2): elaborateColor(4); break; //P4.2
           //case (P4_D*BYTE+3): elaborateColor('G'); break; //P4.3
           //case (P4_D*BYTE+4): break; //P4.4
           case (P4_D*BYTE+5): elaborateColor(4); break; //P4.5
           case (P4_D*BYTE+6): elaborateColor(2); break; //P4.6
           case (P4_D*BYTE+7): elaborateColor(2); break; //P4.7
           //case (P5_D*BYTE+0): break; //P5.0
           case (P5_D*BYTE+1): buttonBackAction(); break;  //P5.1
           case (P5_D*BYTE+2): elaborateColor(3); break; //P5.2
           case (P5_D*BYTE+3): elaborateColor(3); break; //P5.3
           case (P5_D*BYTE+4): elaborateColor(6); break; //P5.4
           //case (P5_D*BYTE+5): elaborateColor(6); break; //P5.5 TIMER A0
           case (P5_D*BYTE+6): elaborateColor(8); break; //P5.6
           //case (P5_D*BYTE+7): elaborateColor(6); break; //P5.7
           //case (P6_D*BYTE+0): break; //P6.0
           //case (P6_D*BYTE+1): elaborateColor(8); break; //P6.1
           //case (P6_D*BYTE+2): elaborateColor(8); break; //P6.2
           //case (P6_D*BYTE+3): elaborateColor(8); break; //P6.3
           case (P6_D*BYTE+4): elaborateColor(8); break; //P6.4
           case (P6_D*BYTE+5): elaborateColor(5); break; //P6.5
           case (P6_D*BYTE+6): elaborateColor(5); break; //P6.6
          // case (P6_D*BYTE+7): elaborateColor(5); break; //P6.7
           //default: exit(1);
        }
    }
}
uint8_t bitofstatus(uint8_t status) {
    int bit_pos=-1;
    int i;
    for (i=0; i<BYTE; i++) {
        if(status & (1 << i)) {
            bit_pos=i;
            return bit_pos;
        }
    }
    return bit_pos;
    //exit(1);
}
void switching(uint8_t status, int8_t port){
    switch(bitofstatus(status)){
        case 0: setArrayInput(port*BYTE); break;
        case 1: setArrayInput(port*BYTE+1); break;
        case 2: setArrayInput(port*BYTE+2); break;
        case 3: setArrayInput(port*BYTE+3); break;
        case 4: setArrayInput(port*BYTE+4); break;
        case 5: setArrayInput(port*BYTE+5); break;
        case 6: setArrayInput(port*BYTE+6); break;
        case 7: setArrayInput(port*BYTE+7); break;
        //default: exit(1);
    }
}
void configureTimersInput(void) {
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
    TIMER_A0->CTL |= TIMER_A_CTL_MC__CONTINUOUS;
    TIMER_A0->CTL |= TIMER_A_CTL_ID_3;
    TIMER_A0->CTL |= TIMER_A_CTL_IE;
    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);
}

bool atLeastOneTrue(void) {
    int i;
    for (i = 0; i < DIMIO; i++) {
        if (array[i]) {
            return true;
        }
    }
    return false;
}

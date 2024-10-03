#include "msp.h"
#include "stdbool.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#define P3_D 1
#define P4_D 2
#define P5_D 3
#define P6_D 4
#define P1_D 0
#define DIMIO 40
#define BYTE 8
#define BUZZER_DUTY_CYCLE  5000
bool array[DIMIO];
bool buzzerBeepFlag = false;
/* Timer_A Compare Configuration Parameter  (PWM) */
/*Timer_A_CompareModeConfig compareConfig_PWM = {
        TIMER_A_CAPTURECOMPARE_REGISTER_4,          // Use CCR3
        TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE,   // Disable CCR interrupt
        TIMER_A_OUTPUTMODE_TOGGLE_SET,              // Toggle output but
        10000                                        // 25% Duty Cycle initially
        };*/
/* Timer_A Up Configuration Parameter */
/*const Timer_A_UpModeConfig upConfig = {
TIMER_A_CLOCKSOURCE_SMCLK,                      // SMCLK = 3 MhZ
        TIMER_A_CLOCKSOURCE_DIVIDER_12,         // SMCLK/12 = 250 KhZ
        20000,                                  // 40 ms tick period
        TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
        TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE,    // Disable CCR0 interrupt
        TIMER_A_DO_CLEAR                        // Clear value
        };*/
void resetArray() {
    int i;
    for(i=0; i<DIMIO; i++) {
        array[i]=false;
    }
}
void setArray(int val) {
    if(val<0 || val>=DIMIO) {
        resetArray();
    }
    else {
        array[val]=true;
    }
}
void configurePorts() {
    /*configure P2.0, P2.1, P2.2 as GPIO (00)*/
    P2->SEL0 &= ~(BIT0 | BIT1 | BIT2);
    P2->SEL1 &= ~(BIT0 | BIT1 | BIT2);
    /*set port 2.0, 2.1, 2.2 as output (1)*/
    P2->DIR |= (BIT0 | BIT1 | BIT2);
    /*clear the pins*/
    P2->OUT &= ~(BIT0 | BIT1 | BIT2);
    /*set P1.1 and P1.4 as GPIO (00)*/
    P1->SEL0 &= ~(BIT1 | BIT4);
    P1->SEL1 &= ~(BIT1 | BIT4);
    /*Set P1.1 and P1.4 as input (0);*/
    P1->DIR &= ~(BIT1 | BIT4);
    /*Pullup mode configuration */
    P1->OUT |= (BIT1 | BIT4);
    /*enable pullup resistor*/
    P1->REN |= (BIT1 | BIT4);
    /*Port 2*/
    //P2->SEL0 = 0x00;
    //P2->SEL1 = 0x00;
    //P2->DIR = 0x00;
    //P2->OUT = 0xFF;
    //P2->REN = 0xFF;
    /*Port 3*/
    P3->SEL0 = 0x00;
    P3->SEL1 = 0x00;
    P3->DIR = 0x00;
    P3->OUT = 0xFF;
    P3->REN = 0xFF;
    /*Port 4*/
    P4->SEL0 = 0x00;
    P4->SEL1 = 0x00;
    P4->DIR = 0x00;
    P4->OUT = 0xFF;
    P4->REN = 0xFF;
    /*Port 5*/
    P5->SEL0 = 0x00;
    P5->SEL1 = 0x00;
    P5->DIR = 0x00;
    P5->OUT = 0xFF;
    P5->REN = 0xFF;
}
void configureInterruptPort() {
    /*P1.1 and P1.4 as HtL transition interrupt*/
    P1->IES |= (BIT1 | BIT4); //HtL BIT1
    /*Enable P1.1 and P1.4 interrupt*/
    P1->IE |= (BIT1 | BIT4);
    /*clear interrupt flag*/
    P1->IFG=0;
    /*play with ISER1 register to set IRQ35 -> P1*/
    NVIC->ISER[1] |= 1 << (PORT1_IRQn & 31);
    /*Port 2*/
    //P2->IES = 0xFF;
    //P2->IE = 0xFF;
    //P2->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT2_IRQn & 31);
    /*Port 3*/
    P3->IES = 0xFF;
    P3->IE = 0xFF;
    P3->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT3_IRQn & 31);
    /*Port 4*/
    P4->IES = 0xFF;
    P4->IE = 0xFF;
    P4->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT4_IRQn & 31);
    /*Port 5*/
    P5->IES = 0xFF;
    P5->IE = 0xFF;
    P5->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT5_IRQn & 31);
    /*Port 6*/
    P6->IES = 0xFF;
    P6->IE = 0xFF;
    P6->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (PORT6_IRQn & 31);
}
/*void buzzerInit() {
    // Configure P2.7 as  buzzer module
    //GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN7, GPIO_PRIMARY_MODULE_FUNCTION);

    /* Configure Timer_A0 for start-up*/
    //Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);
    //Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    // Initialize PWM for buzzer
    //Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM); // Per P2.7
//}*/
/*void buzzerBeep() {
    // Imposta il flag per attivare il beep
        buzzerBeepFlag = true;

        // Avvia il PWM
        Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);
}*/
/**
 * main.c
 */
static int overflow_counter=0;
int counterTrue() {
    int i;
    int counter=0;
    for (i=0; i<DIMIO; i++) {
        if(array[i]==true) {
            counter++;
        }
    }
    return counter;
}

int findTrue() {
    int i;
    for (i=0; i<DIMIO; i++) {
        if(array[i]==true) {
            return i;
        }
    }
    return -1;
}
void elaborateOutput() {
    if (counterTrue()==1) {
        switch(findTrue()) { /*To Generalization in groups of four findTrue()/4*/
            case (P1_D*BYTE+0): break; //P1.0
            case (P1_D*BYTE+1): P2->OUT ^= BIT0; break; //P1.1
            case (P1_D*BYTE+2): break; //P1.2
            case (P1_D*BYTE+3): break; //P1.3
            case (P1_D*BYTE+4): P2->OUT ^= BIT1; break; //P1.4
            case (P1_D*BYTE+5): break; //P1.5
            case (P1_D*BYTE+6): break; //P1.6
            case (P1_D*BYTE+7): break; //P1.7
            //case (P2_D*BYTE+0): break; //P2.0
            //case (P2_D*BYTE+1): break; //P2.1
            //case (P2_D*BYTE+2): break; //P2.2
            //case (P2_D*BYTE+3): break; //P2.3
            //case (P2_D*BYTE+4): break; //P2.4
            //case (P2_D*BYTE+5): break; //P2.5
            //case (P2_D*BYTE+6): break; //P2.6
            //case (P2_D*BYTE+7): break; //P2.7
            case (P3_D*BYTE+0): break; //P3.0
            case (P3_D*BYTE+1): break; //P3.1
            case (P3_D*BYTE+2): break; //P3.2
            case (P3_D*BYTE+3): break; //P3.3
            case (P3_D*BYTE+4): break; //P3.4
            case (P3_D*BYTE+5): break; //P3.5
            case (P3_D*BYTE+6): break; //P3.6
            case (P3_D*BYTE+7): break; //P3.7
            case (P4_D*BYTE+0): P2->OUT ^= BIT2; break; //P4.0
            case (P4_D*BYTE+1): break; //P4.1
            case (P4_D*BYTE+2): break; //P4.2
            case (P4_D*BYTE+3): break; //P4.3
            case (P4_D*BYTE+4): break; //P4.4
            case (P4_D*BYTE+5): break; //P4.5
            case (P4_D*BYTE+6): break; //P4.6
            case (P4_D*BYTE+7): break; //P4.7
            case (P5_D*BYTE+0): break; //P5.0
            case (P5_D*BYTE+1): break; //P5.1
            case (P5_D*BYTE+2): break; //P5.2
            case (P5_D*BYTE+3): break; //P5.3
            case (P5_D*BYTE+4): break; //P5.4
            case (P5_D*BYTE+5): break; //P5.5
            case (P5_D*BYTE+6): break; //P5.6
            case (P5_D*BYTE+7): break; //P5.7
            case (P6_D*BYTE+0): break; //P6.0
            case (P6_D*BYTE+1): break; //P6.1
            case (P6_D*BYTE+2): break; //P6.2
            case (P6_D*BYTE+3): break; //P6.3
            case (P6_D*BYTE+4): break; //P6.4
            case (P6_D*BYTE+5): break; //P6.5
            case (P6_D*BYTE+6): break; //P6.6
            case (P6_D*BYTE+7): break; //P6.7
            //default: exit(1);
        }
        buzzerBeepFlag = true;
    }
}
void configureTimers() {
    /* configure the clock source of timer, use SMCLK = 3 MHz */
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK;
    /* set the operation mode of the timer */
    TIMER_A0->CTL |= TIMER_A_CTL_MC__CONTINUOUS;
    /* use a prescaler to divide the clock by 8 */
    TIMER_A0->CTL |= TIMER_A_CTL_ID_3;
    /* we have a timer running at 6 MHz */

    /* enable overflow interrupt */
    TIMER_A0->CTL |= TIMER_A_CTL_IE;
    /* enable IRQ 9 line for the timer interrupts to catch overflow */
    NVIC->ISER[0] = 1 << ((TA0_N_IRQn) & 31);
}
void switching(uint8_t status, int port){
    switch(status){
        case BIT0: setArray(port*BYTE); break;
        case BIT1: setArray(port*BYTE+1); break;
        case BIT2: setArray(port*BYTE+2); break;
        case BIT3: setArray(port*BYTE+3); break;
        case BIT4: setArray(port*BYTE+4); break;
        case BIT5: setArray(port*BYTE+5); break;
        case BIT6: setArray(port*BYTE+6); break;
        case BIT7: setArray(port*BYTE+7); break;
        //default: exit(1);
    }
}
bool atLeastOneTrue() {
    int i;
    for (i=0; i<DIMIO; i++) {
        if (array[i]) {
            return true;
        }
    }
    return false;
}
void main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    configurePorts();
    configureInterruptPort();
    configureTimers();
    resetArray();
    while(1) {
       __sleep();
    }
}
/*ISR HANDLER FOR PORT1*/
void PORT1_IRQHandler() {
    uint8_t status=P1->IFG;
    switching(status, P1_D);
    P1->IFG &= ~status;
}
/*void PORT2_IRQHandler() {
    uint8_t status=P2->IFG;
    switching(status, P2_D);
    P2->IFG &= ~status;
}*/
void PORT3_IRQHandler() {
    uint8_t status=P3->IFG;
    switching(status, P3_D);
    P3->IFG &= ~status;
}
void PORT4_IRQHandler() {
    uint8_t status=P4->IFG;
    switching(status, P4_D);
    P4->IFG &= ~status;
}
void PORT5_IRQHandler() {
    uint8_t status=P5->IFG;
    switching(status, P5_D);
    P5->IFG &= ~status;
}
void PORT6_IRQHandler() {
    uint8_t status=P6->IFG;
    switching(status, P6_D);
    P6->IFG &= ~status;
}
/* it will be called when TA0CCR0 CCIFG is set */
void TA0_N_IRQHandler(){
    switch(TA0IV){
        case 0xE:
            if(atLeastOneTrue()) {
                if(++overflow_counter == 6){ //6 =  1 sec
                    /* toogle LED */
                    /* Clear timer overflow flag */
                    //TIMER_A0->CTL &= ~TIMER_A_CTL_IFG;
                    // Riavvia il timer dopo l'elaborazione
                    //TIMER_A0->CTL |= TIMER_A_CTL_MC__CONTINUOUS;

                    elaborateOutput();
                    resetArray();
                    /* clear the variable */
                    overflow_counter = 0;
                    // Se il flag per il beep è attivo
                    /*if (buzzerBeepFlag) {
                        buzzerInit();
                        // Inizializza il buzzer per il beep
                        compareConfig_PWM.compareValue = 5000; // Imposta il duty cycle per 100 ms (ajusta questo valore a seconda della tua frequenza PWM)
                        Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM);

                        // Attendi per un breve periodo (100 ms)
                        __delay_cycles(300000); // Aspetta per 100 ms a 3 MHz

                        // Ferma il buzzer
                        compareConfig_PWM.compareValue = 0; // Ferma il PWM
                        Timer_A_initCompare(TIMER_A0_BASE, &compareConfig_PWM);

                        // Resetta il flag
                        buzzerBeepFlag = false;
                    }
                    // Riavvia il timer dopo l'elaborazione
                    TIMER_A0->CTL |= TIMER_A_CTL_MC__CONTINUOUS;*/
                }
            }
        break;
    }
}

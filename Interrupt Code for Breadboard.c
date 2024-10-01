#include "msp.h"
#include "stdbool.h"
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#define P7_D 0
#define P8_D 1
#define P9_D 2
#define P10_D 3
#define P1_D 4
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
    /*Port 7*/
    P7->SEL0 = 0x00;
    P7->SEL1 = 0x00;
    P7->DIR = 0x00;
    P7->OUT = 0xFF;
    P7->REN = 0xFF;
    /*Port 8*/
    P8->SEL0 = 0x00;
    P8->SEL1 = 0x00;
    P8->DIR = 0x00;
    P8->OUT = 0xFF;
    P8->REN = 0xFF;
    /*Port 9*/
    P9->SEL0 = 0x00;
    P9->SEL1 = 0x00;
    P9->DIR = 0x00;
    P9->OUT = 0xFF;
    P9->REN = 0xFF;
    /*Port 10*/
    P10->SEL0 = 0x00;
    P10->SEL1 = 0x00;
    P10->DIR = 0x00;
    P10->OUT = 0xFF;
    P10->REN = 0xFF;
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
    /*Port 7*/
    P7->IES = 0xFF;
    P7->IE = 0xFF;
    P7->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (40 & 31); //Port7_IRQn
    /*Port 7*/
    P8->IES = 0xFF;
    P8->IE = 0xFF;
    P8->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (41 & 31); //Port8_IRQn
    /*Port 7*/
    P9->IES = 0xFF;
    P9->IE = 0xFF;
    P9->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (42 & 31); //Port9_IRQn
    /*Port 7*/
    P10->IES = 0xFF;
    P10->IE = 0xFF;
    P10->IFG = 0x00;
    NVIC->ISER[1] |= 1 << (43 & 31); //Port10_IRQn
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
            case (P7_D*BYTE+0): break; //P7.0
            case (P7_D*BYTE+1): break; //P7.1
            case (P7_D*BYTE+2): break; //P7.2
            case (P7_D*BYTE+3): break; //P7.3
            case (P7_D*BYTE+4): break; //P7.4
            case (P7_D*BYTE+5): break; //P7.5
            case (P7_D*BYTE+6): break; //P7.6
            case (P7_D*BYTE+7): break; //P7.7
            case (P8_D*BYTE+0): break; //P8.0
            case (P8_D*BYTE+1): break; //P8.1
            case (P8_D*BYTE+2): break; //P8.2
            case (P8_D*BYTE+3): break; //P8.3
            case (P8_D*BYTE+4): break; //P8.4
            case (P8_D*BYTE+5): break; //P8.5
            case (P8_D*BYTE+6): break; //P8.6
            case (P8_D*BYTE+7): break; //P8.7
            case (P9_D*BYTE+0): break; //P9.0
            case (P9_D*BYTE+1): break; //P9.1
            case (P9_D*BYTE+2): break; //P9.2
            case (P9_D*BYTE+3): break; //P9.3
            case (P9_D*BYTE+4): break; //P9.4
            case (P9_D*BYTE+5): break; //P9.5
            case (P9_D*BYTE+6): break; //P9.6
            case (P9_D*BYTE+7): break; //P9.7
            case (P10_D*BYTE+0): break; //P10.0
            case (P10_D*BYTE+1): break; //P10.1
            case (P10_D*BYTE+2): break; //P10.2
            case (P10_D*BYTE+3): break; //P10.3
            case (P10_D*BYTE+4): break; //P10.4
            case (P10_D*BYTE+5): break; //P10.5
            case (P10_D*BYTE+6): break; //P10.6
            case (P10_D*BYTE+7): break; //P10.7
            case (P1_D*BYTE+0): break; //P1.0
            case (P1_D*BYTE+1): P2->OUT ^= BIT0; break; //P1.1
            case (P1_D*BYTE+2): break; //P1.2
            case (P1_D*BYTE+3): break; //P1.3
            case (P1_D*BYTE+4): P2->OUT ^= BIT1; break; //P1.4
            case (P1_D*BYTE+5): break; //P1.5
            case (P1_D*BYTE+6): break; //P1.6
            case (P1_D*BYTE+7): break; //P1.7
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
void PORT7_IRQHandler() {
    uint8_t status=P7->IFG;
    switching(status, P7_D);
    P7->IFG &= ~status;
}
void PORT8_IRQHandler() {
    uint8_t status=P8->IFG;
    switching(status, P8_D);
    P8->IFG &= ~status;
}
void PORT9_IRQHandler() {
    uint8_t status=P9->IFG;
    switching(status, P9_D);
    P9->IFG &= ~status;
}
void PORT10_IRQHandler() {
    uint8_t status=P10->IFG;
    switching(status, P10_D);
    P10->IFG &= ~status;
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

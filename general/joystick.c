/*
 * joystick.c
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 *
 */
#include "joystick.h"
#include "difficulty.h"

void upfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: break;
        case DIFFICULTY: upStick_DIFFICULTY(); break;
        case TENTATIVE: break;
        case DOUBLES: break;
        case INFO: break;
        case GAME: break;
        case CHRONOLOGY: break;
        case END: break;
        //default: exit(1);
    }
}
void downfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: break;
        case DIFFICULTY: downStick_DIFFICULTY(); break;
        case TENTATIVE: break;
        case DOUBLES: break;
        case INFO: break;
        case GAME: break;
        case CHRONOLOGY: break;
        case END: break;
       // default: exit(1);
    }
}
void leftfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: break;
        case DIFFICULTY: leftStick_DIFFICULTY(); break;
        case TENTATIVE: break;
        case DOUBLES: break;
        case INFO: break;
        case GAME: break;
        case CHRONOLOGY: break;
        case END: break;
       //default: exit(1);
    }
}
void rightfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: break;
        case DIFFICULTY: rightStick_DIFFICULTY(); break;
        case TENTATIVE: break;
        case DOUBLES: break;
        case INFO: break;
        case GAME: break;
        case CHRONOLOGY: break;
        case END: break;
        //default: exit(1);
    }
}
//Movement functions redirection IMPLEMENT IN YOUR FILES
void NavigateMenu(Move direction) {
    switch(direction) {
        case UP: upfunctions(); break;
        case DOWN: downfunctions(); break;
        case LEFT: leftfunctions(); break;
        case RIGHT: rightfunctions(); break;
        case CENTER: break;
        //default: exit(1);
    }
}
void _adcInit(){
    /* Configures Pin 6.0 and 4.4 as ADC input */
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_TERTIARY_MODULE_FUNCTION);
        GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);

        /* Initializing ADC (ADCOSC/64/8) */
        ADC14_enableModule();
        ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_64, ADC_DIVIDER_8, 0);

        /* Configuring ADC Memory (ADC_MEM0 - ADC_MEM1 (A15, A9)  with repeat)
             * with internal 2.5v reference */

        ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
        ADC14_configureConversionMemory(ADC_MEM0,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

        ADC14_configureConversionMemory(ADC_MEM1,
                ADC_VREFPOS_AVCC_VREFNEG_VSS,
                ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

        /* Enabling the interrupt when a conversion on channel 1 (end of sequence)
         *  is complete and enabling conversions */
        ADC14_enableInterrupt(ADC_INT1);

        /* Enabling Interrupts */
        Interrupt_enableInterrupt(INT_ADC14);
        Interrupt_enableMaster();

        /* Setting up the sample timer to automatically step through the sequence
         * convert.
         */
        ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

        /* Triggering the start of the sample */
        ADC14_enableConversion();
}
void before_ADC(){
    /* Set the core voltage level to VCORE1 */
        PCM_setCoreVoltageLevel(PCM_VCORE1);

        /* Set 2 flash wait states for Flash bank 0 and 1*/
        FlashCtl_setWaitState(FLASH_BANK0, 2);
        FlashCtl_setWaitState(FLASH_BANK1, 2);

        /* Initializes Clock System */
        CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_48);
        CS_initClockSignal(CS_MCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
        CS_initClockSignal(CS_HSMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
        CS_initClockSignal(CS_SMCLK, CS_DCOCLK_SELECT, CS_CLOCK_DIVIDER_1);
        CS_initClockSignal(CS_ACLK, CS_REFOCLK_SELECT, CS_CLOCK_DIVIDER_1);
}
Move findDirection(uint16_t x, uint16_t y) {
    if (y>16200) {
        return UP;
    }
    if(y<200) {
        return DOWN;
    }
    if(x<200) {
        return LEFT;
    }
    if(x>15500) {
        return RIGHT;
    }
    return CENTER;
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

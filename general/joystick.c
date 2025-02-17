/*
 * Title: joystick.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 27 ott 2024
 */
#include "joystick.h"
#include "difficulty.h"
#include "dimension.h"
#include "tentatives.h"
#include "doubles.h"
#include "info.h"
#include "msp.h"
#include "game.h"
#include "chronology.h"
/**
 * @brief Functions that handles the up stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void upfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: upStick_DIMENSION(); break;
        case DIFFICULTY: upStick_DIFFICULTY(); break;
        case TENTATIVE: upStick_TENTATIVE(); break;
        case DOUBLES: upStick_DOUBLES(); break;
        case INFO: upStick_INFO(); break;
        case GAME: break;
        case CHRONOLOGY: upStick_CHRONOLOGY(); break;
        case END: break;
        //default: exit(1);
    }
}
/**
 * @brief Functions that handles the down stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void downfunctions() {
    switch(display_position) {
        case START_GR: break;
       case DIMENSION: downStick_DIMENSION(); break;
        case DIFFICULTY: downStick_DIFFICULTY(); break;
        case TENTATIVE: downStick_TENTATIVE(); break;
        case DOUBLES: downStick_DOUBLES(); break;
        case INFO: downStick_INFO(); break;
        case GAME: break;
        case CHRONOLOGY: downStick_CHRONOLOGY(); break;
        case END: break;
       // default: exit(1);
    }
}
/**
 * @brief Functions that handles the left stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void leftfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: leftStick_DIMENSION(); break;
        case DIFFICULTY: leftStick_DIFFICULTY(); break;
        case TENTATIVE: leftStick_TENTATIVE(); break;
        case DOUBLES: leftStick_DOUBLES(); break;
        case INFO: leftStick_INFO(); break;
        case GAME: leftStick_GAME(); break;
        case CHRONOLOGY: break;
        case END: break;
       //default: exit(1);
    }
}
/**
 * @brief Functions that handles the right stick movement according to the different screens, the ones that doesn't have that option have their field empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void rightfunctions() {
    switch(display_position) {
        case START_GR: break;
        case DIMENSION: rightStick_DIMENSION(); break;
        case DIFFICULTY: rightStick_DIFFICULTY(); break;
        case TENTATIVE: rightStick_TENTATIVE(); break;
        case DOUBLES: rightStick_DOUBLES(); break;
        case INFO: rightStick_INFO(); break;
        case CHRONOLOGY: rightStick_CHRONOLOGY(); break;
        case GAME: break;
        case END: break;
        //default: exit(1);
    }
}
/**
 * @brief According to the Enum declared redirects to one of the appove directional functions
 * @param direction Indicates the direction that each element performs according to the stick position
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
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
/**
 * @brief Initialization of the timer corresponds to the first invocation of the timer and its functionality in order to measure the time passing
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void Timer_Init(void) {
    // Imposta il Timer A0 in modalità up
    TIMER_A0->CTL = TIMER_A_CTL_SSEL__SMCLK | // Sorgente del clock = SMCLK
                    TIMER_A_CTL_MC__CONTINUOUS |
                    TIMER_A_CTL_ID_3 |
                    TIMER_A_CTL_IE;

    TIMER_A0->CCR[0] = 48000; // Imposta il valore di confronto (1 secondo a 48kHz)
    TIMER_A0->CCTL[0] = TIMER_A_CCTLN_CCIE; // Abilita l'interrupt per CCR0
    NVIC_EnableIRQ(TA0_N_IRQn); // Abilita l'interrupt del Timer A0
}
/**
 * @brief Function that stops the system for an amount of time, used primarly for synchronization
 * @param milliseconds Consists in the amount of time we desire to delay
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void delay_ms(uint32_t milliseconds) {
    // Set up Timer32 for 1 ms tick
    TIMER32_1->LOAD = (48000 - 1); // Assuming a 48 MHz clock, 48000 counts for 1 ms
    TIMER32_1->CONTROL = TIMER32_CONTROL_ENABLE | TIMER32_CONTROL_MODE | TIMER32_CONTROL_SIZE;
    uint32_t i;
    for (i = 0; i < milliseconds; i++) {
        // Wait until timer has counted down
        while ((TIMER32_1->RIS & 1) == 0);
        TIMER32_1->INTCLR = 0; // Clear the interrupt flag
    }

    // Stop Timer32
    TIMER32_1->CONTROL = 0;
}
/**
 * @brief Initialization of the adc signal for the joystick, done activationg P6.0 and P4.4, an setting them up witht the tertiary mode
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
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
/**
 * @brief Initialization of the adc signal for the joystick, done activationg P6.0 and P4.4, an setting them up witht the tertiary mode
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
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
/**
 * @brief In order to handle the various interrupts, we have to setup the various sending of interrupts according to an hierarchy. If an interrupt with a higher priority arises, then the below level ones stops. The bottons, so the ports from 1 to 6 have the highest level, because is an instantaneous input, the timer a lower priority, because it has a period of time, but it is not always active, the adc of the joystick instead is always active and continously reads the input of it
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void setupPriorities() {
    // Set priorities for interrupts
   NVIC_SetPriority(ADC14_IRQn, 3);  // Set ADC interrupt priority (lower number = higher priority)
   NVIC_SetPriority(PORT1_IRQn, 1);
   NVIC_SetPriority(PORT3_IRQn, 1);   // Set GPIO Port 3 interrupt priority (higher priority)
   NVIC_SetPriority(PORT4_IRQn, 1);
   NVIC_SetPriority(PORT5_IRQn, 1); // Set GPIO Port 5 interrupt priority (same as Port 3)
   NVIC_SetPriority(PORT6_IRQn, 1);
   NVIC_SetPriority(TA0_N_IRQn, 2);
}
/**
 * @brief method that trigger the activation of the next read of ADC sensor
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void ADC_StartConversion(void) {
    ADC14->CTL0 |= ADC14_CTL0_SC;
}
/**
 * @brief enabling the interrupts for the two joystick channels P6.0 and P4.4
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
void ADC_EnableInterrupts(void) {
    ADC14->IER0 |= BIT0; // Enable interrupt for channel 0 (P6.0)
    ADC14->IER0 |= BIT1; // Enable interrupt for channel 1 (P4.4)
    NVIC->ISER[1] |= (1 << (ADC14_IRQn & 31)); // Enable ADC14 interrupt in NVIC
}
/**
 * @brief Choosing the direction of the joystick according to the position of it
 * @param x The x position from 0 on left to 15700 c.a. on right
 * @param y The y position from 0 on top to 16200 c.a. on bottom
 * @return Move gives and enum in order to determine visually to which category belongs that position
 * @author Matteo Gottardelli (Primary Author & Maintainer
 * @date 2024-10-27
 */
Move findDirection(uint16_t x, uint16_t y) {
    if (y>16000) {
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

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
#include "input.h"
#include "game.h"
#include "gamelogic1.h"
#include "gamelogic2.h"
#include "gamelogic3.h"
#include "chronology.h"

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
// Finite State Machine declaration
typedef struct {
    State state;                          // Current state of the FSM
    void (*state_function)(void);         // Pointer to the state function
} StateMachine;
StateMachine fsm[] = {
    {START, fn_START},
    {KEY_WOUT_DOUB, fn_KEY_WOUT_DOUB},
    {KEY_WH_DOUB, fn_KEY_WH_DOUB},
    {RESET_TENT, fn_RESET_TENT},
    {WAIT, fn_WAIT},
    {ELABORATE, fn_ELABORATE},
    {INSERT_COLOR, fn_INSERT_COLOR},
    {WAIT_FULL, fn_WAIT_FULL},
    {ELIMINATE_COLOR, fn_ELIMINATE_COLOR},
    {ELABORATE_TENT, fn_ELABORATE_TENT},
    {INCREMENT_TENT, fn_INCREMENT_TENT},
    {GAME_OVER, fn_GAME_OVER},
    {EASY_MODE, fn_EASY_MODE},
    {MEDIUM_MODE, fn_MEDIUM_MODE},
    {DIFFICULT_MODE, fn_DIFFICULT_MODE},
    {ELABORATE_RESULT, fn_ELABORATE_RESULT},
    {WIN, fn_WIN}
};
Game game;
Tentative tentative;
Graphics_State display_position=GAME;
State current_state=START;
Graphics_Rectangle upperRect={0, 0, 128, 32};
Graphics_Rectangle upperRectCH={0, 0, 128, 16};
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
        case GAME:  labelText.string="MASTERMIND"; break;
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
//Niccolò Cristoforetti's code
Graphics_Button tent_buttons[]={  //TENTATIVE state part
    {FOCUSED, {TENT_DIM/4+1, 32+TENT_DIM/4+1, TENT_DIM/2+TENT_DIM/4-1, 32+TENT_DIM/2+TENT_DIM/4-1}, {"", false}},
    {STANDARD, {1, 32+TENT_DIM+1, TENT_DIM-1, 32+TENT_DIM*2-1}, {"3", false}},
    {STANDARD, {TENT_DIM+1, 32+TENT_DIM+1, TENT_DIM*2-1, 32+TENT_DIM*2-1}, {"5", false}},
    {STANDARD, {TENT_DIM*2+1, 32+TENT_DIM+1, TENT_DIM*3-1, 32+TENT_DIM*2-1}, {"7", false}},
    {STANDARD, {TENT_DIM*3+1, 32+TENT_DIM+1, TENT_DIM*4-1, 32+TENT_DIM*2-1}, {"10", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}},
    {STANDARD, {0, 0, 0, 0}, {"", false}}
};
Graphics_Button text_no_tent={DISABLED, {TENT_DIM+1, 32+2, TENT_DIM*4-1, 32+TENT_DIM-1}, {"NO TRIES", false}};
Graphics_Button start_button={FOCUSED, {32, 96, 96, 112}, {"START", false}};
Graphics_Button chronology_buttons[]={  //CHRONOLOGY state part
    {STANDARD, {1, 24+1, 128-1, 56-1}, {"", false}},
    {STANDARD, {1, 56+1, 128-1, 88-1}, {"", false}},
    {STANDARD, {1, 88+1, 128-1, 120-1}, {"", false}}
};
Graphics_Button other_buttons[]={
    {DISABLED, {1, 16+1, 128-1, 24-1}, {"", false}}, 
    {DISABLED, {1, 120+1, 128-1, 128-1}, {"", false}}
};
//Daniele Calvo's code
Graphics_Text doubles_text={{"Doubles"}, false};  //DOUBLE state part
Graphics_Text doubles_description[]={ 
    {{"Possibility of "}, false},
    {{"the same color "}, false},
    {{"repeated or not"}, false}};
Graphics_Button doubles_buttons[]={ 
    {FOCUSED, {80, 37, 110, 57}, {{"No"}, false}},
    {STANDARD, {0,0,0,0}, {{""}, false}},
    {STANDARD, {0,0,0,0}, {{""}, false}}};
   
Graphics_Text info_texts[]={   //INFO state part
    {{" "}, false},
    {{"Dimension: "}, false},
    {{"Difficulty: "}, false},
    {{"Doubles: "}, false},
    {{"Tentatives: "}, false}
};
Graphics_Text info_texts_results[]={ 
    {{" "}, false},
    {{" "}, false},
    {{" "}, false},
    {{" "}, false},
    {{" "}, false}};
Graphics_Button info_buttons[]={ 
    {STANDARD, {0,0,0,0}, {{""}, false}},
    {STANDARD, {0,0,0,0}, {{""}, false}}};
//GAME PASSWORD
Graphics_Circle circles[]={
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0},
   {0, 0, 0, 0}
};
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
            case CHRONOLOGY: sizes[i]=ARRAY_SIZE(chronology_buttons); break;
            case END: sizes[i]=1; break;
            default: exit(1);
        }
    }
}
volatile uint32_t timerTicks = 0;
uint32_t Timer_getValue(void) {
    return timerTicks; // Restituisce il numero di tick del timer
}
//BOOLEANS
volatile bool interruptFlag=false;
bool exit_gamelogic=false;
int main(void) {
    srand((unsigned)time(NULL));
    WDT_A_holdTimer();
    //Setup Infrastructure
    hardware_Init();
    setSizes();
    setupPriorities();
    ADC_EnableInterrupts();
    Timer_Init();
    while(1) {
       interruptFlag=false;
       exit_gamelogic=false;
       if(display_position<ERROR_GR) {
           labelDefining(display_position);
           (*gfsm[display_position].state_function)();
       }
       else {
           return 0;
       }
       if(configurationGame) {
           while(1) {
               if (current_state < ERROR) {
                   (*fsm[current_state].state_function)(); // Call the appropriate state function
               } else {
                   // Clean up and exit if in ERROR state
                   if (current_state == ERROR) {
                       deallocate_Char((char*) game.seq_to_guess); // Deallocate sequence memory
                       deallocate_Char((char*) game.chronology); // Deallocate chronology memory
                       deallocate_Bool(game.flags); //Deallocate flag memory
                       exit_gamelogic=true; // Exit the loop
                   }
               }
               //CASES OF BREAK IN ORDER TO GO TO INTERRUPT
               if(current_state==WAIT || current_state==WAIT_FULL) {
                   exit_gamelogic=true;
               }
               if(exit_gamelogic) {
                   break;
               }
           }
       }
       __enable_interrupt();
       ADC14_enableConversion();
       ADC_StartConversion(); // Start ADC conversion
      while(1) {
          __sleep();
          ADC14_disableConversion();
          if (interruptFlag) {
              break;
          }
          ADC14_enableConversion();
      }
      releaseMutex();
      __disable_interrupt();
    }
}
/*ISR HANDLER FOR PORTS 1-6*/
/*void PORT1_IRQHandler() {
    //while(P1->IN);
    uint8_t status=P1->IFG;
    switching(status, P1_D);
    P1->IFG &= 0;
}*/
/*void PORT2_RQHandler() {
    while(P2->IN);
    uint8_t status=P2->IFG;
    elaborateOutput();
    P2->IFG &= ~status;
}*/
void PORT3_IRQHandler(void) {
    bool internalFlag=false;
    if (P3->IFG & BIT0) {
        while(!(P3->IN & BIT0));
        internalFlag=true;
    }
    if (P3->IFG & BIT1) {
        while(!(P3->IN & BIT1));
        internalFlag=true;
    }
    if (P3->IFG & BIT2) {
        while(!(P3->IN & BIT2));
        internalFlag=true;
    }
    if (P3->IFG & BIT3) {
        while(!(P3->IN & BIT3));
        internalFlag=true;
    }
    if (P3->IFG & BIT4) {
        while(!(P3->IN & BIT4));
        internalFlag=true;
    }
    if (P3->IFG & BIT5) {
        while(!(P3->IN & BIT5));
        internalFlag=true;
    }
    if (P3->IFG & BIT6) {
       while(!(P3->IN & BIT6));
       internalFlag=true;
    }
    /*if (P3->IFG & BIT7) {
        while(!(P3->IN & BIT7));
        internalFlag=true;
    }*/
    uint8_t status=P3->IFG-0x80;
    if(internalFlag) {
        functionPinsDefault(status, P3_D);
    }
    P3->IFG &= ~status;
    printf("Port 3");
    fflush(stdout);
}
void PORT4_IRQHandler() {
    bool internalFlag=false;
    if (P4->IFG & BIT0) {
        while(!(P4->IN & BIT0));
        internalFlag=true;
    }
    /*if (P4->IFG & BIT1) {
        while(!(P4->IN & BIT1));
        internalFlag=true;
    }*/
    if (P4->IFG & BIT2) {
        while(!(P4->IN & BIT2));
        internalFlag=true;
    }
    /*if (P4->IFG & BIT3) {
        while(!(P4->IN & BIT3));
        internalFlag=true;
    }*/
    if (P4->IFG & BIT4) {
        //DEBOUNCE
        GPIO_clearInterruptFlag(GPIO_PORT_P4, GPIO_PIN4);
        /*static uint32_t lastInterruptTime = 0;
        uint32_t currentTime = Timer_getValue();

        if (currentTime - lastInterruptTime > DEBOUNCE_TIME) {
            interruptFlag = true;
            lastInterruptTime = currentTime;
        }*/
    }
    if (P4->IFG & BIT5) {
        while(!(P4->IN & BIT5));
        internalFlag=true;
    }
    if (P4->IFG & BIT6) {
       while(!(P4->IN & BIT6));
       internalFlag=true;
    }
    if (P4->IFG & BIT7) {
        while(!(P4->IN & BIT7));
        internalFlag=true;
    }
    uint8_t status=P4->IFG;
    if(internalFlag) {
        functionPinsDefault(status, P4_D);
    }
    P4->IFG &= ~status;
    printf("Port 4");
    fflush(stdout);
}
void PORT5_IRQHandler(void) {
   bool internalFlag=false;
   /*if (P5->IFG & BIT0) {
       while(P5->IN & BIT0);
       internalFlag=true;
   }*/
   if (P5->IFG & BIT1) {
       while(!(P5->IN & BIT1));
       internalFlag=true;
   }
   if (P5->IFG & BIT2) {
       while(!(P5->IN & BIT2));
       internalFlag=true;
   }
   if (P5->IFG & BIT3) {
       while(!(P5->IN & BIT3));
       internalFlag=true;
   }
   if (P5->IFG & BIT4) {
       while(!(P5->IN & BIT4));
       internalFlag=true;
   }
   if (P5->IFG & BIT5) {
       while(!(P5->IN & BIT5));
       internalFlag=true;
   }
   if (P5->IFG & BIT6) {
      while(!(P5->IN & BIT6));
      internalFlag=true;
   }
   /*if (P5->IFG & BIT7) {
       while(!(P5->IN & BIT7));
       internalFlag=true;
   }*/
   uint8_t status=P5->IFG-0x81;
   if(internalFlag) {
       functionPinsDefault(status, P5_D);
   }
   P5->IFG &= ~status;
   printf("Port 5");
   fflush(stdout);
}
void PORT6_IRQHandler() {
    bool internalFlag=false;
    if (P6->IFG & BIT0) {
        //DEBOUNCE
        GPIO_clearInterruptFlag(GPIO_PORT_P6, GPIO_PIN0);
        /*static uint32_t lastInterruptTime = 0;
        uint32_t currentTime = Timer_getValue();

        if (currentTime - lastInterruptTime > DEBOUNCE_TIME) {
            interruptFlag = true;
            lastInterruptTime = currentTime;
        }*/
    }
    if (P6->IFG & BIT1) {
        while(!(P6->IN & BIT1));
        internalFlag=true;
    }
    if (P6->IFG & BIT2) {
        while(!(P6->IN & BIT2));
        internalFlag=true;
    }
    if (P6->IFG & BIT3) {
        while(!(P6->IN & BIT3));
        internalFlag=true;
    }
    if (P6->IFG & BIT4) {
        while(!(P6->IN & BIT4));
        internalFlag=true;
    }
    if (P6->IFG & BIT5) {
        while(!(P6->IN & BIT5));
        internalFlag=true;
    }
    if (P6->IFG & BIT6) {
       while(!(P6->IN & BIT6));
       internalFlag=true;
    }
    /*if (P6->IFG & BIT7) {
        while(!(P6->IN & BIT7));
        internalFlag=true;
    }*/
    uint8_t status=P6->IFG;
    if(internalFlag) {
        functionPinsDefault(status, P6_D);
    }
    P6->IFG &= ~status;
    printf("Port 6");
    fflush(stdout);
}
//Timer Interrupt
/* it will be called when TA0CCR0 CCIFG is set */
void TA0_N_IRQHandler(){
    switch(TA0IV){
        case 0xE:
            if(atLeastOneTrue()) {
                overflow_counter++;
                if(overflow_counter == 2 && !configurationGame){ //6 =  1 sec
                    elaborateOutput();
                    resetArrayInput();
                    interruptFlag=true;
                    // clear the variable
                    overflow_counter = 0;
                    ADC14_disableConversion();
                }else {
                    if(overflow_counter == 6 && configurationGame){ //6 =  1 sec
                        elaborateOutput();
                        resetArrayInput();
                        interruptFlag=true;
                        // clear the variable
                        overflow_counter = 0;
                        ADC14_disableConversion();
                    }
                }
                printf("Overflow %d\n", overflow_counter);
                fflush(stdout);
            }
        break;
    }
}
//ADC Interrupt
void ADC14_IRQHandler(void)
{
    acquireMutex();
    uint16_t x, y;
    uint64_t status= ADC14_getEnabledInterruptStatus();
    ADC14_clearInterruptFlag(status);
    /* ADC_MEM1 conversion completed */
    if(status & ADC_INT1)
    {
            /* Store ADC14 conversion results */
            resultsBuffer[0] = ADC14_getResult(ADC_MEM0);
            resultsBuffer[1] = ADC14_getResult(ADC_MEM1);
            x=resultsBuffer[0];
            y=resultsBuffer[1];
            ADC14_clearInterruptFlag(ADC_INT1);
            NavigateMenu(findDirection(x, y));
    }
    releaseMutex();
    int i;
    for (i=0; i<100000; i++);
    printf("X: %d, Y: %d\n", x, y);
    fflush(stdout);
    delay_ms(50);
}

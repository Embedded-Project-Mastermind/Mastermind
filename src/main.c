//
//  main.c
//  Mastermind Program
//
//  Created by Matteo Gottardelli on 27/09/24.
//

#include <stdio.h>
#include "game.h"
#include "fsm.h"
// Finite State Machine declaration
typedef struct {
    State state;                          // Current state of the FSM
    void (*state_function)(void);         // Pointer to the state function
} StateMachine;

// Finite State Machine implementation
StateMachine fsm[] = {
    {START, fn_START},
    {KEY_WOUT_DOUB, fn_KEY_WOUT_DOUB},
    {KEY_WH_DOUB, fn_KEY_WH_DOUB},
    {RESET_TENT, fn_RESET_TENT}
};
Game game;
Tentative tentative;
State current_state=START;
void main(void) {
    srand((unsigned)time(NULL)); // Seed the random number generator
    while (1) {
        if (current_state < ERROR) {
            (*fsm[current_state].state_function)(); // Call the appropriate state function
        } else {
            // Clean up and exit if in ERROR state
            if (current_state == ERROR) {
                deallocate_Char(game.seq_to_guess); // Deallocate sequence memory
                deallocate_Char(game.chronology); // Deallocate chronology memory
                break; // Exit the loop
            }
        }
    }
}

/*
 * Title: fsm.h
 * Primary Authors: Alessandro Benassi, Daniele Calvo, Matteo Gottardelli, Niccolò Cristoforetti
 * Helpers: -
 • Maintainability: Alessandro Benassi, Daniele Calvo, Matteo Gottardelli, Niccolò Cristoforetti
 * Date Creation: 5 ott 2024
 */

#ifndef FSM_H_
#define FSM_H_
#include "msp.h"
#include "stdbool.h"
//COSTANTS
#define COLORS 8 //Colors Available based on the number you have
#define MAX_TENTS 30 //Is no tentatives are selected, after a certain number we stop
                     //in order to not saturate the memory
#define EMERGERCY_TENT 7
#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
/* ENUM Declaration */
typedef enum {START, KEY_WOUT_DOUB, KEY_WH_DOUB, RESET_TENT, WAIT, INSERT_COLOR, WAIT_FULL, ELIMINATE_COLOR, ELABORATE_TENT, INCREMENT_TENT, GAME_OVER, EASY_MODE, MEDIUM_MODE, DIFFICULT_MODE, ELABORATE_RESULT, WIN, ERROR} State;
/* Struct Declaration*/
typedef struct Game {
    int16_t dim;                   // Dimension of the sequence
    int8_t difficulty;           // Difficulty level of the game
    bool doubles;              // Flag to indicate if doubles are allowed
    int16_t count_tent;           // Count of current attempts
    int16_t tentatives;            // Total number of allowed attempts
    int8_t* seq_to_guess;        // Sequence to be guessed
    int8_t* chronology;          // History of attempts
    bool* flags;               // Flag of boolean
} Game;

typedef struct {
    int16_t count;                // Count of user attempts
    int16_t dim;                  // Dimension of user's sequence
    int8_t* seq_user;           // User's guessed sequence
    int8_t* sol_user;
} Tentative;
void acquireMutex(void);
void releaseMutex(void);
/*Global variables*/
extern Game game;                  // Game struct instance
extern Tentative tentative;        // Tentative struct instance
extern State current_state;    // Initialize current state
extern int i, j;                     //Variables acting like counters for for-cycles
extern volatile bool interruptFlag;
extern volatile bool mutex;
#endif /* FSM_H_ */

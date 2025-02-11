//
//  fsm.h
//  Mastermind Program
//
//  Created by Matteo Gottardelli on 27/09/24.
//
#ifndef fsm_h
#define fsm_h

/* Constants */
#define COLORS 6                // Number of colors available
#define DIFFICULTY 'A'         // Default difficulty level
#define TENTATIVES 10          // Number of attempts allowed
#define DIM 4                   // Dimension of the sequence
#define DOUBLES false           // Whether doubles are allowed

/* ENUM Declaration */
typedef enum {START, KEY_WOUT_DOUB, KEY_WH_DOUB, RESET_TENT, WAIT, ELABORATE, INSERT_COLOR, WAIT_FULL, ELIMINATE_COLOR, ELABORATE_TENT, INCREMENT_TENT, GAME_OVER, EASY_MODE, MEDIUM_MODE, DIFFICULT_MODE, ELABORATE_RESULT, WIN, ERROR} State;

/* Struct declarations */
typedef struct {
    int dim;                   // Dimension of the sequence
    char difficulty;           // Difficulty level of the game
    bool doubles;              // Flag to indicate if doubles are allowed
    int count_tent;           // Count of current attempts
    int tentatives;            // Total number of allowed attempts
    char* seq_to_guess;        // Sequence to be guessed
    char* chronology;          // History of attempts
    bool* flagsGuess;               // Flag of boolean for the seq to guess part
    bool* flagsUsr;               // Flag of boolean for the seq user part
} Game;

typedef struct {
    int count;                // Count of user attempts
    int dim;                  // Dimension of user's sequence
    char* seq_user;           // User's guessed sequence
} Tentative;
/* Global variables */
extern Game game;                  // Game struct instance
extern Tentative tentative;        // Tentative struct instance
extern State current_state;    // Initialize current state
extern int i, j;                     //Variables acting like counters for for-cycles
extern char temp;                // used to pass converted vale into char(color) crom a function to another
extern int value;                 //used to pass input value from a function to another
extern bool selection;            // true if text_selection -> buttons menu, false if text selection -> colors menu
#endif /* fsm_h */

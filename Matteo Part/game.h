#ifndef GAME_H
#define GAME_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

/* Constants */
#define COLORS 6                // Number of colors available
#define DIFFICULTY 'A'         // Default difficulty level
#define TENTATIVES 10          // Number of attempts allowed
#define DIM 4                   // Dimension of the sequence
#define DOUBLES false           // Whether doubles are allowed

/* ENUM Declaration */
typedef enum {START, KEY_WOUT_DOUB, KEY_WH_DOUB, RESET_TENT, ERROR} State;

/* Struct declarations */
typedef struct {
    int dim;                   // Dimension of the sequence
    char difficulty;           // Difficulty level of the game
    bool doubles;              // Flag to indicate if doubles are allowed
    int count_tent;           // Count of current attempts
    int tentatives;            // Total number of allowed attempts
    char* seq_to_guess;        // Sequence to be guessed
    char* chronology;          // History of attempts
} Game;

typedef struct {
    int count;                // Count of user attempts
    int dim;                  // Dimension of user's sequence
    char* seq_user;           // User's guessed sequence
} Tentative;
/* Global variables */
extern Game game;                  // Game struct instance
extern Tentative tentative;        // Tentative struct instance
extern State current_state;  // Initialize current state
/* Function declarations */
void fn_START(void);                          // Function for the START state
void fn_KEY_WOUT_DOUB(void);                  // Function for the KEY_WOUT_DOUB state
void fn_KEY_WH_DOUB(void);                     // Function for the KEY_WH_DOUB state
void fn_RESET_TENT(void);                      // Function for the RESET_TENT state
void initGame(int dim, char diff, bool doubles, int tents); // Initializes the game parameters
void deallocate_Char(char* array);            // Deallocates character array memory
void deallocate_Int(int* array);               // Deallocates integer array memory
int* key_generation_wout_doub(void);          // Generates key without doubles
int* key_generation_wh_doub(void);            // Generates key with doubles
bool presence_Double(int* array, int value, int dim); // Checks if a value is already present in the array
char int_Conversion_to_Char(int index);       // Converts an integer index to a character
void crypt_sequence_Int_Char(int* arr1, char* arr2, int dim); // Crypts an integer array into a character array
void continue_Key_Decryption(int* sequence);  // Continues decryption process for the generated key
void resetTentative(void);                     // Resets the tentative state for the user's guesses
void makeArrayEmpty_Char(char* array, int par1, int par2); // Initializes a character array to zero
void makeArrayEmpty_Int(int* array, int par1, int par2);   // Initializes an integer array to zero

#endif

//
//  game.h
//  Mastermind Program
//
//  Created by Matteo Gottardelli on 27/09/24.
//
#ifndef GAME_H
#define GAME_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"

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

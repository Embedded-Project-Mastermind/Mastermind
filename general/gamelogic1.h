//
//  game.h
//  Mastermind Program
//
//  Created by Matteo Gottardelli on 27/09/24.
//
#ifndef GAMELOGIC1_H
#define GAMELOGIC1_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"
#include "joystick.h"

/* Function declarations */
void fn_START(void);                          // Function for the START state
void fn_KEY_WOUT_DOUB(void);                  // Function for the KEY_WOUT_DOUB state
void fn_KEY_WH_DOUB(void);                     // Function for the KEY_WH_DOUB state
void fn_RESET_TENT(void);                      // Function for the RESET_TENT state
void initGame(int16_t dim, int8_t diff, bool doubles, int16_t tents); // Initializes the game parameters
void allocate_in_Heap_Int(int16_t** array, int16_t par1, int16_t par2);   //Memory allocation for a int16_t array
void allocate_in_Heap_Char(int8_t** array, int16_t par1, int16_t par2);  //Memory allocation for a int8_tacter array
void allocate_in_Heap_Bool(bool** array, int16_t par1, int16_t par2);  //Memory allocation for a boolean array
void deallocate_Char(int8_t* array);          // Deallocates int8_tacter array memory
void deallocate_Int(int16_t* array);               // Deallocates int16_teger array memory
void deallocate_Bool(bool* array);             // Deallocates boolean array memory
int16_t* key_generation_wout_doub(void);          // Generates key without doubles
int16_t* key_generation_wh_doub(void);            // Generates key with doubles
bool presence_Double(int16_t* array, int16_t value, int16_t dim); // Checks if a value is already present in the array
int8_t int_Conversion_to_Char(int16_t index);       // Converts an int16_teger index to a int8_tacter
void crypt_sequence_Int_Char(int16_t* arr1, int8_t* arr2, int16_t dim); // Crypts an int16_teger array int16_to a int8_tacter array
void continue_Key_Decryption(int16_t* sequence);  // Continues decryption process for the generated key
void resetTentative(void);                     // Resets the tentative state for the user's guesses
void makeArrayEmpty_Char(int8_t* array, int16_t par1, int16_t par2); // Initializes a int8_tacter array to zero
void makeArrayEmpty_Int(int16_t* array, int16_t par1, int16_t par2);   // Initializes a boolean array to zero
void makeArrayEmpty_Bool(bool* array, int16_t par1, int16_t par2);   // Initializes a boolean array to false

#endif

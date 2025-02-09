/*
 * Title: gamelogic1.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 27 set 2024
 */
#ifndef GAMELOGIC1_H
#define GAMELOGIC1_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"
#include "joystick.h"

/**
 * @brief Function that deallocated dynamic allocated memory and is called if there are unexpected behaviors in the code
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void emergency();
/**
 * @brief Call function when START of the finite state machine is called and initializes the game after selecting the elements
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void fn_START(void);
/**
 * @brief Call function when KEY_WOUT_DOUB of the finite state machine is called and generates a sequence to find with no duplicates
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void fn_KEY_WOUT_DOUB(void);
/**
 * @brief Call function when KEY_WH_DOUB of the finite state machine is called and generates a sequence to find with duplicates
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void fn_KEY_WH_DOUB(void);
/**
 * @brief Call function when RESET_TENT of the finite state machine is called after each tentative is sent successfully and resets the elements of the current Tentative
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void fn_RESET_TENT(void);
/**
 * @brief Initialize the game with parameters selected from the GUI interface from DIMENSION, DIFFICULTY, TENTATIVES, DOUBLES
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void initGame(int16_t dim, int8_t diff, bool doubles, int16_t tents);
/**
 * @brief Allocation for an integer array, ensuring that it is not already allocated
 * @param array Double Integer Reference for allocation Matrix
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void allocate_in_Heap_Int(int16_t** array, int16_t par1, int16_t par2);
/**
 * @brief Allocation for a character array, ensuring that it is not already allocated
 * @param array Double Char Reference for allocation Matrix
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void allocate_in_Heap_Char(int8_t** array, int16_t par1, int16_t par2);
/**
 * @brief Allocation for a boolean array, ensuring that it is not already allocated
 * @param array Double Boolean Reference for allocation Matrix
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void allocate_in_Heap_Bool(bool** array, int16_t par1, int16_t par2);  //Memory allocation for a boolean array
/**
 * @brief Deallocate memory for a character array setting then that allocation to null for being sure
 * @param array Char array reference for a deallocation
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void deallocate_Char(int8_t* array);
/**
 * @brief Deallocate memory for an integer array setting then that allocation to null for being sure
 * @param array Integer array reference for a deallocation
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void deallocate_Int(int16_t* array);
/**
 * @brief Deallocate memory for a boolean array setting then that allocation to null for being sure
 * @param array Boolean array reference for a deallocation
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void deallocate_Bool(bool* array);             // Deallocates boolean array memory
/**
 * @brief Generation of a random key that allows the presence of duplicates colors
 * @return returns the array generated to a reference
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
int16_t* key_generation_wh_doub(void);
/**
 * @brief Generation of a random key that doesn't allow the presence of duplicates colors
 * @return returns the array generated to a reference
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
int16_t* key_generation_wout_doub(void);
/**
 * @brief Check if the array has already a value that I would like to insert in it
 * @param array Current array from which we would want to verify the presence
 * @param value Corresponds to the value we would like to verify the presence of
 * @param dim Total length of the array, we are currently passing
 * @return bool - returns the result of this if - TRUE it is already present, FALSE that color is not present in the sequence
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
bool presence_Double(int16_t* array, int16_t value, int16_t dim);
/**
 * @brief Convertion of a element from the integer format to the char format
 * @param index Integer format value
 * @return int8t returned char format value
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
int8_t int_Conversion_to_Char(int16_t index);
/**
 * @brief Convertion of an array from the integer format to the char format
 * @param arr1 Integer format array
 * @param arr2 Char format array
 * @param dim Total dimension of the array
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void crypt_sequence_Int_Char(int16_t* arr1, int8_t* arr2, int16_t dim);
/**
 * @brief Analysis and parsing of the integer sequence to the char one, with an appropriate deallocation of the integer one
 * @param sequence Parsed sequence in integer format
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void continue_Key_Decryption(int16_t* sequence);
/**
 * @brief After each input sequence is analyzed the tentative is all reinitialized with an incrementation of the tentative count
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void resetTentative(void);
/**
 * @brief Initialization for a character array setting to its default state
 * @param array Char array reference for a deallocation
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void makeArrayEmpty_Char(int8_t* array, int16_t par1, int16_t par2);
/**
 * @brief Initialization for an integer array setting to its default state
 * @param array Integer array reference for a deallocation
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void makeArrayEmpty_Int(int16_t* array, int16_t par1, int16_t par2);
/**
 * @brief Initialization for a boolean array setting to its default state
 * @param array Boolean array reference for a deallocation
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void makeArrayEmpty_Bool(bool* array, int16_t par1, int16_t par2);
/**
 * @brief Generation of a random integer with two limits
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
int random_int(int16_t min, int16_t max);
#endif

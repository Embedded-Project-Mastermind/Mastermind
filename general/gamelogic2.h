/*
 * Title: gamelogic2.h
 * Primary Authors: Alessandro Benassi, Daniele Calvo
 * Helpers: Matteo Gottardelli
 * Maintainability: Alessandro Benassi
 * Date Creation: 27 set 2024
 */
#ifndef GAMELOGIC2_H
#define GAMELOGIC2_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"
#include "gamelogic1.h"
#include "game.h"

#define OPTIONS 3  //number of button options: 1=input, 2=confirm, 3=back

/* Function declarations */
/**
 * @brief state while he's waiting an input
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_WAIT(void);                 //Function for WAIT state
/**
 * @brief state for when he received an input (now useless)
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_ELABORATE(void);            //Function for ELABORATE state
/**
 * @brief state for inserting the color choosen by the user in its sequence
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_INSERT_COLOR(void);         //Function for INSERT_COLOR state
/**
 * @brief state while he's waiting an input with the user's sequence full
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_WAIT_FULL(void);            //Function for WAIT_FULL state
/**
 * @brief state for deleting the last color of the user's sequence
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_ELIMINATE_COLOR(void);      //Function for ELIMINATE_COLOR state
/**
 * @brief returns if the user’s sequence is empty or not
 * @return boolean
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
bool is_empty(void);                // checks if the array seq_user  is empty
/**
 * @brief returns if the user’s sequence is full or not
 * @return boolean
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
bool is_full(void);                 // checks if the array seq_user  is full
/**
 * @brief (Outdated) it was the main menu for the logic test on console
 * @param a boolean to switch from two distinct menu
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void text_selection(bool sel);      //selects the test to display
/**
 * @brief (Outdated) print to indicate the full state of the array on console
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void full_text(void);                  //displays the text if the arrya is full
/**
 * @brief (Outdated) print on console of the user's sequence
 * @param a pointer to the sequence
 * @param the dimension of the array for the user's sequence
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void print_sequence(int8_t* seq, int16_t dim);  //to print the sequence
/**
 * @brief inserts the selected color into the user's sequence if space is available
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void insert_color();   //Function to insert color in the array seq_user
/**
 * @brief deletes the last color into the user's sequence if it is not empty
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void eliminate_color(void);   //Function to eliminate color from the array seq_user

/* Old functions. Now totally useless 
bool elaborate(void);   //Function to verify if the input is valid (work in progress)
int read_input(int16_t dim);        //reads input value from keyboard and verifies if correct
void handle_wait(int16_t value);      //menu selection(buttons or colors)
void wait_handle(void);   //Function that waits for an input from the buttons(interrupt)
void wait_full(void);     //Function to wait if the array is full 
*/

#endif

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
void fn_WAIT(void);                 //Function for WAIT state
void fn_ELABORATE(void);            //Function for ELABORATE state
void fn_INSERT_COLOR(void);         //Function for INSERT_COLOR state
void fn_WAIT_FULL(void);            //Function for WAIT_FULL state
void fn_ELIMINATE_COLOR(void);      //Function for ELIMINATE_COLOR state
bool is_empty(void);                // checks if the array seq_user  is empty
bool is_full(void);                 // checks if the array seq_user  is full
void text_selection(bool sel);      //selects the test to display
void full_text(void);                  //displays the text if the arrya is full
int read_input(int16_t dim);        //reads input value from keyboard and verifies if correct
void handle_wait(int16_t value);      //menu selection(buttons or colors)
void print_sequence(int8_t* seq, int16_t dim);  //to print the sequence
void wait_handle(void);   //Function that waits for an input from the buttons(interrupt)
void wait_full(void);     //Function to wait if the array is full 
void insert_color();   //Function to insert color in the array seq_user
void eliminate_color(void);   //Function to eliminate color from the array seq_user
bool elaborate(void);   //Function to verify if the input is valid (work in progress)

#endif

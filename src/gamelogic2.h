//
//  gamelogic2.h
//  Mastermind Program
//
//  Created by Alessandro Benassi and Daniele Calvo on 29/09/24.
//
#ifndef GAMELOGIC2_H
#define GAMELOGIC2_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"
#include "gamelogic1.h"

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
int read_input(int dim);        //reads input value from keyboard and verifies if correct
void handle_wait(int value);      //menu selection(buttons or colors)
void print_sequence(char* seq, int dim);  //to print the sequence
void wait_handle(void);   //Function that waits for an input from the buttons(interrupt)
void wait_full(void);     //Function to wait if the array is full 
void insert_color(char color);   //Function to insert color in the array seq_user
void eliminate_color(void);   //Function to eliminate color from the array seq_user
bool elaborate(void);   //Function to verify if the input is valid (work in progress)

#endif

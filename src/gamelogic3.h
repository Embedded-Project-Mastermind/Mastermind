//
//  gamelogic3.h
//  Mastermind
//
//  Created by Niccolò Cristoforetti on 29/09/24.
//

#ifndef GAMELOGIC3_H
#define GAMELOGIC3_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"
#include "gamelogic1.h"

//Function declarations
void fn_ELABORATE_TENT(void);  //Function for ELABORATE_TENT state
void fn_INCREMENT_TENT(void);  //Function for INCREMENT_TENT state
void fn_GAME_OVER(void);  //Function for GAME_OVER state
void fn_EASY_MODE(void);  //Function for EASY_MODE state
void fn_MEDIUM_MODE(void); //Function for MEDIUM_MODE state
void fn_DIFFICULT_MODE(void);  //Function for DIFFICULT_MODE state
void fn_ELABORATE_RESULT(void); //Function for ELABORATE_RESULT state
void fn_WIN(void);  //Function for WIN state
int checkIfTenctOrCorrection(char c); //Function that checks if the sequence is a tenctative or a correction. Returns a int for set the right index in the chronology
void insertInChronology(char* seq); //Function that inserts sequence or sequence correction in chronology
void incrementTent(void); //Function that increases the number of tenctative
bool checkIfGameOver(void);  //Function that checks if the maximum number of attempts has been reached
char check_difficulty(void);  //Function that checks the difficulty degree
void correctionsEasyMode(void); //Function that transforms the seq_user into corrections in EASY_MODE
void correctionsMediumMode(void); //Function that transforms the seq_user into corrections in MEDIUM_MODE
void correctionsDifficultMode(void); //Function that transforms the seq_user into corrections in DIFFICULT_MODE
void printLastTentativeInChronology(void);  //Function that prints the last sequence the last sequence inserted in the chronology with the respective corrections
bool winCondition(void); //Function that checks if the next state is WIN or not
#endif

/*
 * Title: gamelogic3.h
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 29 set 2024
 */

#ifndef GAMELOGIC3_H
#define GAMELOGIC3_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#include "fsm.h"
#include "gamelogic1.h"

//Function declarations

/**
 * @brief Function for ELABORATE_TENT state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_ELABORATE_TENT(void);

/**
 * @brief Function for INCREMENT_TENT state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_INCREMENT_TENT(void);

/**
 * @brief Function for GAME_OVER state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_GAME_OVER(void);

/**
 * @brief Function for EASY_MODE state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_EASY_MODE(void);

/**
 * @brief Function for MEDIUM_MODE state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_MEDIUM_MODE(void);

/**
 * @brief Function for DIFFICULT_MODE state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_DIFFICULT_MODE(void);

/**
 * @brief Function for ELABORATE_RESULT state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_ELABORATE_RESULT(void);

/**
 * @brief Function for WIN state
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void fn_WIN(void);

/**
 * FUNCTION DEPRECATED
 * @brief Function that checks if the sequence is a tentative or a correction.
 * @param integer
 * @return integer for set the right index in the chronology
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
//int16_t checkIfTenctOrCorrection(int8_t c);

/**
 * @brief Function that inserts sequence results in chronology
 * @param array integer for the sequence results
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void insertInChronologyRes(int8_t* seq);

/**
 * @brief Function that inserts sequence in chronology
 * @param array integer for the sequence
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void insertInChronologyColor(int8_t* seq);

/**
 * @brief Function that increases the number of tentative
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void incrementTent(void);

/**
 * @brief Function that checks if the maximum number of attempts has been reached
 * @param void
 * @return boolean that check the gameover state
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
bool checkIfGameOver(void);

/**
 * @brief Function that checks the difficulty degree
 * @param void
 * @return integer that shows the difficulty degree
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
int8_t check_difficulty(void);

/**
 * @brief Function that transforms the seq_user into corrections in EASY_MODE
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void correctionsEasyMode(void);

/**
 * @brief Function that transforms the seq_user into corrections in MEDIUM_MODE
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void correctionsMediumMode(void);

/**
 * @brief Function that transforms the seq_user into corrections in DIFFICULT_MODE
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void correctionsDifficultMode(void);

/**
 * @brief Function that prints the last sequence inserted in the chronology with the respective corrections
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
void printLastTentativeInChronology(void);

/**
 * @brief Function that checks if the next state is WIN or not
 * @param void
 * @return boolean that check the win state
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-09-29
 */
bool winCondition(void);
#endif

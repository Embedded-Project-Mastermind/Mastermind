/*
 * implementations.h
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 */

#ifndef IMPLEMENTATIONS_H_
#define IMPLEMENTATIONS_H_
#include "stdio.h"
#include "stdlib.h"
#include "graphics.h"

void graphics_Init();
void hardware_Init();
void reset_Screen();
//FOLLOWING DEFINE THE GRAPHIC FUNCTIONS USED IN C FILE

//FUNCTIONS FOR STATES
void fn_START_GR(void);
void fn_DIMENSION(void);
void fn_DIFFICULTY(void);
void fn_TENTATIVE(void);
void fn_DOUBLES(void);
void fn_INFO(void);
void fn_GAME(void);
void fn_CHRONOLOGY(void);
void fn_END(void);
#endif /* IMPLEMENTATIONS_H_ */

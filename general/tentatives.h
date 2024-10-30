/*
 * tentatives.h
 *
 *  Created on: 10 ott 2024
 *      Author: niccolocristoforetti
 */

#ifndef TENTATIVES_H_
#define TENTATIVES_H_
#include "stdio.h"
#include "stdlib.h"
#include "implementations.h"
#include "graphics.h"

#define TENT_DIM 32

extern Graphics_Button tent_buttons[];
Graphics_Button other_things[];

void handlePressure_TENTATIVE();
void drawTentatives(void);
void fn_TENTATIVE(void);
void upStick_TENTATIVE();
void downStick_TENTATIVE();
void leftStick_TENTATIVE();
void rightStick_TENTATIVE();

#endif /* TENTATIVES_H_ */

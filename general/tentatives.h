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

void drawTentatives(int elems);
void fn_TENTATIVE(void);

#endif /* TENTATIVES_H_ */

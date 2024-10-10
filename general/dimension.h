/*
 * dimension.h
 *
 *  Created on: 10 ott 2024
 *      Author: AlessandroBenassi
 */

#ifndef DIMENSION_H_
#define DIMENSION_H_

#include "implementations.h"
#include "graphics.h"


void drawDimension(int32_t elems);
void fn_DIMENSION(void); //ricordarsi di rimuoverla da implementations.h e implementations.c

//extern declaretion
extern Graphics_Button dim_buttons[];  //da implementare nel main

#endif /* DIMENSION_H_ */

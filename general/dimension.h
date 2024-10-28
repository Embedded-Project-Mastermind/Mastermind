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


void drawDimension(); //draws buttons
void fn_DIMENSION(void); //general function for scenario drawing
void handleFont(); //manages the font dimension for the buttons
void upStick_DIMENSION(); //handles the up movement of the stick
void downStick_DIMENSION(); //handles the down movement of the stick
void leftStick_DIMENSION(); //handles the left movement of the stick
void rightStick_DIMENSION(); //handles the right movement of the stick
void handlePressure_DIMENSION();
//extern declaretion
extern Graphics_Button dim_buttons[];  //array of buttons declaration

#endif /* DIMENSION_H_ */

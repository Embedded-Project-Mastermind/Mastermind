/*
 * chronology.h
 *
 *  Created on: 31 ott 2024
 *      Author: niccolocristoforetti
 */

#ifndef CHRONOLOGY_H_
#define CHRONOLOGY_H_
#include "graphics.h"
#include "implementations.h"
#include "input.h"

//extern bool configurationGame;

extern Graphics_Button chronology_buttons[];
extern Graphics_Button other_buttons[];
Graphics_Button return_to;

void drawChronology(void);
void fn_CHRONOLOGY(void);
void upStick_CHRONOLOGY();
void downStick_CHRONOLOY();
void rightStick_CHRONOLOGY();


#endif /* CHRONOLOGY_H_ */

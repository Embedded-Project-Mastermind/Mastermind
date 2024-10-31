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
extern Graphics_Button tent_number[];
Graphics_Button return_to;
int16_t pos; //var for manage the tent outputs after having overtaken three tentative

void drawChronology(void);
void fn_CHRONOLOGY(void);
void upStick_CHRONOLOGY();
void downStick_CHRONOLOY();
void rightStick_CHRONOLOGY();
void updatePos();


#endif /* CHRONOLOGY_H_ */

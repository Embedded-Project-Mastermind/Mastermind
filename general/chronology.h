/*
 * Title: chronology.h
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: Matteo Gottardelli
 * Maintainability: Niccolò Cristoforetti, Matteo Gottardelli
 * Date Creation: 31 ott 2024
 */

#ifndef CHRONOLOGY_H_
#define CHRONOLOGY_H_
#include "graphics.h"
#include "implementations.h"
#include "input.h"
#include "game.h"
#define BASIC_OFFSET 15
#define RADIUS 6
#define MAX_DIM 6

//extern bool configurationGame;

extern Graphics_Button other_buttons[];
Graphics_Button return_to;
extern int16_t pos_chronology; //var for manage the tent outputs after having overtaken three tentative

typedef struct Graphics_Chronology {
    Graphics_Button button;
    Graphics_Rectangle num_rect;
    Graphics_Text num;
    Graphics_Circle chrono_circles[MAX_DIM];
} Graphics_Chronology;
extern Graphics_Chronology chronology[];
void drawChronology(void);
void fn_CHRONOLOGY(void);
void populateChronologyCircles(int16_t offset, int16_t radius, Graphics_Chronology chronology, int16_t index);
int16_t char_Conversion_to_Int(int8_t index);
void upStick_CHRONOLOGY();
void downStick_CHRONOLOGY();
void rightStick_CHRONOLOGY();
void updatePos();


#endif /* CHRONOLOGY_H_ */

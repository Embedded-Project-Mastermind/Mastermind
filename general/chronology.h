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
    Graphics_Button chrono_buttons[MAX_DIM];
} Graphics_Chronology;
extern Graphics_Chronology chronology[];

/**
 * @brief function that create buttons and text for the Chronology screen
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void drawChronology(void);

/**
 * @brief functions that create the Chronology screen starting from resetting the previous screen
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void fn_CHRONOLOGY(void);

/**
 * @brief populate the cHronology circle with their colors
 * @param radius dimension of the circle
 * @param value position of the sequence
 * @param index that indicates History of attempts
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void populateChronologyCircles(int16_t radius, int16_t value, int16_t index);

/**
 * @brief converts the number associated to the color to its color char
 * @param integer
 * @return char
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
int16_t char_Conversion_to_Int(int8_t index);

/**
 * @brief function that populate chronology buttons (related to corrections)
 * @param value position of the sequence
 * @param index that indicates History of attempts
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void populateChronologyButtons(int16_t value, int16_t index);

/**
 * @brief function that draw corrections below circles
 * @param buttons buttons related to corrections
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void drawPastResults(Graphics_Button* buttons);

/**
 * @brief manage what to do when the user moves the stick up
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void upStick_CHRONOLOGY();

/**
 * @brief manage what to do when the user moves the stick down
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void downStick_CHRONOLOGY();

/**
 * @brief manage what to do when the user moves the stick right
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void rightStick_CHRONOLOGY();

/**
 * @brief populate the last attempts of the chronology or the ones that were selected by the joystick
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void updatePos();


#endif /* CHRONOLOGY_H_ */

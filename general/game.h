/*
 * Title: game.h
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Alessandro Benassi, Matteo Gottardelli
 * Date Creation: 31 ott 2024
 */

#ifndef GAME_H_
#define GAME_H_
#include "graphics.h"
#include "implementations.h"
#include "input.h"
#define YLEVEL_OFFSET 32
//Declaration of dynamic elements in GAME Section
extern bool configurationGame;
extern Graphics_Circle circles[];
extern Graphics_Rectangle textRect;
extern int16_t color_selected;
/**
 * @brief Implicit Call that is invoked when we arrive at GAME state in GUI FSM and primarly draw the static elements and dynamic ones
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
 */
void fn_GAME(void);
/**
 * @brief According to the inputed color, the leds are turned on according to that color (ORANGE case it will be P1.0, for the others will be a direct correspondes to combination of P2.0, P2.1, P2.2
 * @param c Consist in an integer denoting a custom coding of colors (more clarity in input.c)
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
 */
void elaborateColor(int16_t c);
/**
 * @brief According to the dimension selected in GUI menu, are preallocated empty circles that change dynamically position and size according to the number, because they have to fit on the screen
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
 */
void initCircles();
/**
 * @brief Initialization effective of the circles according to the inputed parameters
 * @param offset Determine the distance from the leftest pixel of the leftest circle and the left border
 * @param radius Circle radius, distance from the center to the circle border
 * @param value_y Position of y axis according to the screen
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
void populateCircles(int16_t offset, int16_t radius, int16_t value_y);
/**
 * @brief Management and color of the circles on screen
 * @param circs The circle initialized array that handles the handle the color of each element in the array
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
void drawCircles(Graphics_Circle* circs);
/**
 * @brief Action that the menu performs when the stick goes left, primarly changing selection and imposing logic visual limits
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
void leftStick_GAME();
/**
 * @brief Action that the menu performs when the stick goes left, primarly changing selection and imposing logic visual limits
 * @param color Graphics color definition according to the integer inputed and according to that the circle will be colored
 * @return int32, returns the graphics color in order to color the circle
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
int32_t selectColor(int16_t color);
/**
 * @brief Effective function that refresh the status of GAME Section, when an update happen
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper & Maintainer)
 * @date 2024-10-31
*/
void displayResultsOnScreen();
#endif /* GAME_H_ */

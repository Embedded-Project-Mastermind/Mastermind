/*
 * Title: difficulty.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 10 ott 2024
 */

#ifndef DIFFICULTY_H_
#define DIFFICULTY_H_
#include "stdio.h"
#include "stdlib.h"
#include "implementations.h"
#define DIFF_DIM 20
#define DIFF_TEXT 4
#define DIFF_TYPES 4

/**
 * @brief Implicit Call that is invoked when we arrive at DIFFICULTY state in GUI FSM
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void fn_DIFFICULTY(void);
/**
 * @brief Function that draws the interface of difficulty section, 3 buttons to select difficulty and the others for prev (go to DIMENSION) and next (go to TENTATIVES)
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawDifficulty();
/**
 * @brief Action that the menu performs when the stick goes up, primarly changing selection and imposing logic visual limits
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void upStick_DIFFICULTY();
/**
 * @brief Action that the menu performs when the stick goes down, primarly changing selection and imposing logic visual limits
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void downStick_DIFFICULTY();
/**
 * @brief Action that the menu performs when the stick goes left, primarly changing selection and imposing logic visual limits
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void leftStick_DIFFICULTY();
/**
 * @brief Action that the menu performs when the stick goes right, primarly changing selection and imposing logic visual limits
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void rightStick_DIFFICULTY();
/**
 * @brief Function that handles pressure of confirm button when we are in DIFFICULTY section
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handlePressure_DIFFICULTY();
/**
 * @brief Draw Text Description according to the difficulty selected in order to explain to the user what that means
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawText();
//Declaration of dynamic elements in DIFFICULTY Section
extern Graphics_Button diff_buttons[];
extern Graphics_Text explain[DIFF_TEXT][DIFF_TYPES];
#endif /* DIFFICULTY_H_ */

/*
 * Title: tentatives.h
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 10 ott 2024
 */

#ifndef TENTATIVES_H_
#define TENTATIVES_H_
#include "stdio.h"
#include "stdlib.h"
#include "implementations.h"
#include "graphics.h"

#define TENT_DIM 32

//Declaration of dynamic elements in TENTATIVES Section
extern Graphics_Button tent_buttons[];
extern Graphics_Button other_things[];

/**
 * @brief manages the choice of tentative trough the pressure of the button (except to prev and next)
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handlePressure_TENTATIVE();

/**
 * @brief function that create buttons and text for the Tentatives screen
 * @param integer for the number of buttons of the Tentatives screen
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawTentatives(int elems);

/**
 * @brief functions that create the tentatives screen starting from resetting the previous screen
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void fn_TENTATIVE(void);

/**
 * @brief manage what to do when the user moves the stick up
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void upStick_TENTATIVE();

/**
 * @brief manage what to do when the user moves the stick down
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void downStick_TENTATIVE();

/**
 * @brief manage what to do when the user moves the stick to the left
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void leftStick_TENTATIVE();

/**
 * @brief manage what to do when the user moves the stick to the right
 * @param void
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void rightStick_TENTATIVE();

#endif /* TENTATIVES_H_ */

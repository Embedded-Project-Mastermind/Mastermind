/*
 * Title: dimension.h
 * Primary Authors: Alessandro Benassi
 * Helpers: -
 * Maintainability: Alessandro Benassi
 * Date Creation: 10 ott 2024
 */

#ifndef DIMENSION_H_
#define DIMENSION_H_

#include "implementations.h"
#include "graphics.h"
/**
 * @brief Function that draws the interface of dimension section, 4 buttons to select the dimension and the others for prev (go to START_GR) and next (go to DIFFICULTY)
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawDimension();
/**
 * @brief Implicit Call, invoked when we arrive at DIMENSION state in GUI FSM, initializes variables and draws the interface
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void fn_DIMENSION(void);
/**
 * @brief makes the font of the DIMENSION's buttons bigger and avoids conflict with next and prev buttons
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handleFont();
/**
 * @brief handles the up movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void upStick_DIMENSION();
/**
 * @brief handles the down movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void downStick_DIMENSION();
/**
 * @brief handles the left movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void leftStick_DIMENSION();
/**
 * @brief handles the right movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void rightStick_DIMENSION();
/**
 * @brief Handles the pressure of confirm button in the DIMENSION section
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handlePressure_DIMENSION();
//extern declaretion
extern Graphics_Button dim_buttons[];

#endif /* DIMENSION_H_ */

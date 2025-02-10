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
 * @brief draws buttons
 * @return TODO: Describe return value.
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawDimension(); //draws buttons
/**
 * @brief general function for scenario drawing
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void fn_DIMENSION(void); //general function for scenario drawing
/**
 * @brief manages the font dimension for the buttons
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handleFont(); //manages the font dimension for the buttons
/**
 * @brief handles the up movement of the stick
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void upStick_DIMENSION(); //handles the up movement of the stick
/**
 * @brief handles the down movement of the stick
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void downStick_DIMENSION(); //handles the down movement of the stick
/**
 * @brief handles the down movement of the stick
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void leftStick_DIMENSION(); //handles the left movement of the stick
/**
 * @brief handles the right movement of the stick
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void rightStick_DIMENSION(); //handles the right movement of the stick
/**
 * @brief extern declaretion
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handlePressure_DIMENSION();
//extern declaretion
extern Graphics_Button dim_buttons[];  //array of buttons declaration

#endif /* DIMENSION_H_ */

/*
 * Title: info.h
 * Primary Authors: Daniele Calvo
 * Helpers: Matteo Gottardelli
 * Maintainability: Daniele Calvo
 * Date Creation: 5 ott 2024
 */

#ifndef INFO_H_
#define INFO_H_
#include "implementations.h"
// arrays with buttons and texts of this interface.
// Previously implemented in the main
extern Graphics_Text info_texts[];
extern Graphics_Text info_texts_results[];
extern Graphics_Button info_buttons[];

/**
 * @brief manages how to set all info's interface, also calling the functions to create the texts and the buttons
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void change_screen_i(void);
/**
 * @brief calls all needed
 * functions to change the previous interface
 * with the one of the doubles' state
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void fn_INFO(void);

/**
 * @brief manage what to do when the user moves the stick up
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void upStick_INFO();
/**
 * @brief manage what to do when the user moves the stick down
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void downStick_INFO();
/**
 * @brief manage what to do when the user moves the stick left
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void leftStick_INFO();
/**
 * @brief manage what to do when the user moves the stick right
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void rightStick_INFO();
/**
 * @brief calls the function for the "back" and "next" button's handle
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Matteo Gottardelli (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-10
 */
void handlePressure_INFO();
void buttons_INFO();

#endif /* INFO_H_ */

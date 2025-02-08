/*
 * Title: doubles.h
 * Primary Authors: Daniele Calvo
 * Helpers: Alessandro Benassi
 * Maintainability: Matteo Gottardelli
 * Date Creation: 10 ott 2024
 */

#ifndef DOUBLES_H_
#define DOUBLES_H_
#include "implementations.h"
// arrays with buttons and texts of this interface.
// Previously implemented in the main
extern Graphics_Text doubles_text;
extern Graphics_Text doubles_description[];
extern Graphics_Button doubles_buttons[];

/**
 * @brief initializes the texts and draw them
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void create_doubles_text(void);
/**
 * @brief initializes the buttons, putting them on an ordered array and drawing them
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void create_doubles_button(void);
/**
 * @brief manages how to set all doubles' interface, also calling the functions to create the texts and the buttons
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void change_screen_d(void);
/**
 * @brief calls all needed
 * functions to change the previous interface
 * with the one of the doubles' state
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void fn_DOUBLES(void);

/**
 * @brief manages the changes of our doubles variable and the shown text on our button (except to prev and next)
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void handlePressure_DOUBLES();
/**
 * @brief manage what to do when the user moves the stick up
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void upStick_DOUBLES();
/**
 * @brief manage what to do when the user moves the stick down
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void downStick_DOUBLES();
/**
 * @brief manage what to do when the user moves the stick left
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void leftStick_DOUBLES();
/**
 * @brief manage what to do when the user moves the stick right
 * @return void
 * @author Daniele Calvo (Primary author)
 * @author Alessandro Benassi (Helper)
 * @author Matteo Gottardelli (Maintainer)
 * @date 2024-10-10
 */
void rightStick_DOUBLES();
void buttons_DOUBLES();

#endif /* DOUBLES_H_ */

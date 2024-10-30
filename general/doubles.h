/*
 * doubles.h
 *
 *  Created on: 10 Oct 2024
 *      Author: calvo
 */

#ifndef DOUBLES_H_
#define DOUBLES_H_
#include "implementations.h"
// arrays with buttons and texts of this interface.
// Previously implemented in the main
extern Graphics_Text doubles_text;
extern Graphics_Text doubles_description[];
extern Graphics_Button doubles_buttons[];

// functions needed to create the interface
void create_doubles_text(void);
void create_doubles_button(void);
void change_screen_d(void); //to call the other two functions and set minor things
void fn_DOUBLES(void);

// functions needed to interact with the interface
void handlePressure_DOUBLES();
void upStick_DOUBLES();
void downStick_DOUBLES();
void leftStick_DOUBLES();
void rightStick_DOUBLES();
void buttons_DOUBLES();

#endif /* DOUBLES_H_ */

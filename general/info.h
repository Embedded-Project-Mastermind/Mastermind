/*
 * info.h
 *
 *  Created on: 10 Oct 2024
 *      Author: calvo
 */

#ifndef INFO_H_
#define INFO_H_
#include "implementations.h"
// arrays with buttons and texts of this interface.
// Previously implemented in the main
extern Graphics_Text info_texts[];
extern Graphics_Text info_texts_results[];
extern Graphics_Button info_buttons[];

//functions needed to create the interface
void change_screen_i(void);
void fn_INFO(void);

//functions needed to interact with the interface
void upStick_INFO();
void downStick_INFO();
void leftStick_INFO();
void rightStick_INFO();
void handlePressure_INFO();
void buttons_INFO();

#endif /* INFO_H_ */

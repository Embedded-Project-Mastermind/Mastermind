/*
 * Title: implementations.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Niccolò Cristoforetti
 * Maintainability: Daniele Calvo
 * Date Creation: 5 ott 2024
 */


#ifndef IMPLEMENTATIONS_H_
#define IMPLEMENTATIONS_H_
#include "stdio.h"
#include "stdlib.h"
#include "graphics.h"
#define BORDER 2

/**
 * @brief initializes the display and drivers
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void graphics_Init(void);
/**
 * @brief initializa all the hardware, including ports and interrupts
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void hardware_Init(void);
/**
 * @brief it resets all default's colors and clear the display
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void reset_Screen(void);
//FOLLOWING DEFINE THE GRAPHIC FUNCTIONS USED IN C FILE
extern Graphics_Rectangle upperRect;
extern Graphics_Button prevButton;
extern Graphics_Button nextButton;
extern Graphics_Rectangle upperRectCH;
extern Graphics_Text labelText;
extern uint8_t position;
//FIND POSITION RECT
/**
 * @brief gives back the x of the center of the given rectangle
 * @param the rectangle
 * @return the x of the center of the given rectangle
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int32_t getCenteredX(Graphics_Rectangle rect);
/**
 * @brief gives back the y of the center of the given rectangle
 * @param the rectangle
 * @return the y of the center of the given rectangle
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int32_t getCenteredY(Graphics_Rectangle rect);
//COLOR CHOICE FUNCTIONS
/**
 * @brief chooses the color of the button given its current state
 * @param the current state of the button
 * @param the current color of the button
 * @return the choosen color
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int32_t chooseColorRect(Button_State state, int32_t color);
/**
 * @brief chooses the color of the text on the button given the button's current state
 * @param the current state of the button
 * @param the current color of the text
 * @return the choosen color
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int32_t chooseColorText(Button_State state, int32_t color);
//FUNCTIONS STATUS
/**
 * @brief it handles the status change of old focused button
 * @param the buttons' array
 * @param the position of the old focused button
 * @param the size opf the array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handleOut(Graphics_Button array[], uint8_t position, int8_t size);
/**
 * @brief it handles the status change of new focused button
 * @param the buttons' array
 * @param the position of the new focused button
 * @param the size opf the array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handleIn(Graphics_Button array[], uint8_t position, int8_t size);
//FUNCTIONS DRAW
/**
 * @brief it draws a rectangle with a text centered in it
 * @param the rectangle
 * @param the rectangle's color
 * @param the text
 * @param the text's color
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void rectangleWithText(Graphics_Rectangle rect, int32_t colorRect, Graphics_Text text, int32_t colorText);
/**
 * @brief finds the selected button in all the buttons of an interface
 * @param the buttons' array
 * @param the size of the array
 * @return the position of the button in the "selected" state (if no button is selected, -1)
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int8_t findSelected(Graphics_Button array[], int8_t size);
/**
 * @brief draws the button in the given position with the right color
 * @param the button
 * @param the button's color
 * @param the button's text color
 * @param then position
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void drawButton(Graphics_Button button, int32_t rect_color, int32_t text_color, int8_t pos_selected);
/**
 * @brief visually updates a button when it is focused
 * @param the state of the button
 * @param the button
 * @param the button's color
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void focusedHandle(Button_State state, Graphics_Rectangle rect, int32_t color);
/**
 * @brief selects the currently focused button
 * @param buttons' array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handleSelection(Graphics_Button array[]);
/**
 * @brief Resets all buttons to "STANDARD"
 * @param buttons' array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handleDeselection(Graphics_Button array[]);
//buttons back and next handler
/**
 * @brief handles the prev and next buttons
 * @param the buttons' array of the current interface
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handle_buttons(Graphics_Button array[]);
//FUNCTION INIT
/**
 * @brief it finalizes out buttons' array putting in it the prev and next button and modifing the states
 * @param the buttons' array of the current interface
 * @param the size of the array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void initArray(Graphics_Button array[], int size);
//FUNCTIONS FOR STATES
void fn_END(void);
#endif /* IMPLEMENTATIONS_H_ */

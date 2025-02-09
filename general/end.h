/*
 * Title: end.h
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 7 nov 2024
 */

#ifndef END_H_
#define END_H_
#include "stdio.h"
#include "stdlib.h"
#include "fsm.h"
#include "implementations.h"
#include "graphics.h"
#include "bitmap.h"
#include "start.h"


extern Graphics_Button gameover_button;
extern Graphics_Button win_button;

/**
 * @brief draws the end screen, displaying either a win or game over message.
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-11-07
 */
void drawEnd();
/**
 * @brief initializes and displays the end screen
 * @return void
 * @author Niccolò Cristoforetti (Primary author)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-11-07
 */
void fn_END(void);

//From start.h
uint16_t encodeColor(uint8_t r, uint8_t g, uint8_t b);

#endif /* END_H_ */

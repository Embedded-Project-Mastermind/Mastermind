/*
 * buttons.h
 *
 *  Created on: 11 ott 2024
 *      Author: matteogottardelligmail.com
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "fsm.h"
#define DEBOUNCE_TIME 20

void button_Init();
void buttonBackAction();
void buttonConfirmAction();
void functionPinsDefault(uint8_t status, int8_t port);
#endif /* BUTTONS_H_ */

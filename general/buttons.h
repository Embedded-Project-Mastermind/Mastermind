/*
 * Title: buttons.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Alessandro Benassi
 * Maintainability: Matteo Gottardelli
 * Date Creation: 11 ott 2024
 */

#ifndef BUTTONS_H_
#define BUTTONS_H_
#include "fsm.h"
#define DEBOUNCE_TIME 20

/**
 * @brief Sets up launchpad pins connected for the buttons (P3.5 and P5.1)
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
void button_Init();
/**
 * @brief Implements back button action that redirects in eliminate colored circle state if there was at least one input, instead outputs that is empty
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
void buttonBackAction();
/**
 * @brief Implements confirm button action that manage its input according to the state you are in. STARTGR has only one button, so directly redicts; DIMENSION, DIFFICULTY, TENTATIVE, DOUBLES, INFO are menu features and they have their own logic; GAME allows sequence processing only if the sequence is full; CHRONOLOGY and END don't use this button
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
void buttonConfirmAction();
/**
 * @brief Deprecated, using switching function, it is only a bridge function now
 * @param status int that represents the current configuration of IFG register, so the flag register that handles interrupts on a port
 * @param port int that represents a port on which an interrupt has occurred
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @author Alessandro Benassi (Helper)
 * @date 2024-10-11
 */
void functionPinsDefault(uint8_t status, int8_t port);
#endif /* BUTTONS_H_ */

/*
 * Title: difficulty.c
 * Primary Authors: Alessandro Benassi
 * Helpers: -
 * Maintainability: Alessandro Benassi
 * Date Creation: 10 ott 2024
 */
#include "dimension.h"
#include "implementations.h"
/**
 * @brief dFunction that draws the interface of dimension section, 4 buttons to select the dimension and the others for prev (go to START_GR) and next (go to DIFFICULTY)
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void drawDimension() {
    int i;
    for (i=0; i<sizes[DIMENSION]; i++) {
        if (i<sizes[DIMENSION]-2) {
            Graphics_setFont(&grContext, &g_sFontCm20);
            drawButton(dim_buttons[i], STANDARD_COLOR, SELECTED_COLOR, findSelected(dim_buttons, sizes[DIMENSION]));
        }
        else {
            Graphics_setFont(&grContext, &g_sFontFixed6x8);
            drawButton(dim_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, findSelected(dim_buttons, sizes[DIMENSION]));
        }
    }
}
/**
 * @brief makes the font of the DIMENSION's buttons bigger and avoids conflict with next and prev buttons
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handleFont(){
    if (position<sizes[DIMENSION]-2) {
        Graphics_setFont(&grContext, &g_sFontCm20);
    }
    else{
        Graphics_setFont(&grContext, &g_sFontFixed6x8);
    }
}
/**
 * @brief Implicit Call, invoked when we arrive at DIMENSION state in GUI FSM, initializes variables and draws the interface
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void fn_DIMENSION(void) {
    reset_Screen();
    initArray(dim_buttons, sizes[DIMENSION]);
    rectangleWithText(upperRect, FILL_UPPER_RECT, labelText, SELECTED_COLOR);
    drawDimension();
}
/**
 * @brief handles the up movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void upStick_DIMENSION(){
    if(position>1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position-2;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}
/**
 * @brief handles the down movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void downStick_DIMENSION(){
    if(position<3){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position=position+2;
            handleFont();
            handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
    else if(position==3 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED ){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position=position+2;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}
/**
 * @brief handles the left movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void leftStick_DIMENSION(){
    if((position%2)==1){
        handleFont();
        handleOut(dim_buttons, position, sizes[DIMENSION]);
        position--;
        handleFont();
        handleIn(dim_buttons, position, sizes[DIMENSION]);
    }
}
/**
 * @brief handles the right movement of the stick, changing the selected element if the action can be performed
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void rightStick_DIMENSION(){
    if((position%2)==0){
        if(position<4){
            handleFont();
            handleOut(dim_buttons, position, sizes[DIMENSION]);
            position++;
            handleFont();
            handleIn(dim_buttons, position, sizes[DIMENSION]);
        }
        if(position==4 && dim_buttons[sizes[DIMENSION]-1].state!=DISABLED){
           handleFont();
           handleOut(dim_buttons, position, sizes[DIMENSION]);
           position++;
           handleFont();
           handleIn(dim_buttons, position, sizes[DIMENSION]);
       }
     }
}
/**
 * @brief Handles the pressure of confirm button in the DIMENSION section
 * @return void
 * @author Alessandro Benassi (Primary Author & Maintainer)
 * @date 2024-10-10
 */
void handlePressure_DIMENSION() {
    game.dim=atoi((char*)dim_buttons[position].text.string);
    handleSelection(dim_buttons);
}

/*
 * Title: implementations.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: Niccolò Cristoforetti
 * Maintainability: Matteo Gottardelli
 * Date Creation: 5 ott 2024
 */
#include "implementations.h"
#include "graphics.h"
#include "joystick.h"
#include "buttons.h"
#include "dimension.h"
#include "difficulty.h"
#include "tentatives.h"
#include "doubles.h"
#include "info.h"
#include "input.h"
#include "chronology.h"
#include "game.h"

volatile bool mutex=false;
/**
 * @brief it resets all default's colors and clear the display
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void reset_Screen(void) {
    Graphics_setFont(&grContext, &g_sFontFixed6x8); //resets the font to the standard one, probably not necessary but anyways it's good practice to put it
    Graphics_setForegroundColor(&grContext, STANDARD_COLOR); //sets foreground to black
    Graphics_setBackgroundColor(&grContext, SELECTED_COLOR); //sets background to white for the borders
    Graphics_clearDisplay(&grContext);
}
/**
 * @brief initializes the display and drivers
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void graphics_Init(void) {
    //INITIALIZE DISPLAY AND DRIVERS
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    Graphics_initContext(&grContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setFont(&grContext, &g_sFontFixed6x8);
    reset_Screen();
}
/**
 * @brief gives back the x of the center of the given rectangle
 * @param the rectangle
 * @return the x of the center of the given rectangle
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int32_t getCenteredX(Graphics_Rectangle rect) {
    return (rect.xMax+rect.xMin)/2;
}
/**
 * @brief gives back the y of the center of the given rectangle
 * @param the rectangle
 * @return the y of the center of the given rectangle
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
int32_t getCenteredY(Graphics_Rectangle rect) {
    return (rect.yMax+rect.yMin)/2;
}
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
int32_t chooseColorRect(Button_State state, int32_t color) {
    int32_t c;
    switch(state) {
        case FOCUSED: c=STANDARD_COLOR; break;
        case STANDARD: c=color; break;
        case SELECTED: c=SELECTED_COLOR; break;
        case DISABLED: c=DISABLED_COLOR; break;
        default: exit(1);
    }
    return c;
}
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
int32_t chooseColorText(Button_State state, int32_t color) {
    int32_t c;
    switch(state) {
        case FOCUSED: c=BORDER_FOCUSED_COLOR; break;
        case STANDARD: c=color; break;
        case SELECTED: c=BORDER_SELECTED_COLOR; break;
        case DISABLED: c=BORDER_SELECTED_COLOR; break;
        default: exit(1);
    }
    return c;
}
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
void focusedhandle(Button_State state, Graphics_Rectangle rect, int32_t color) {
    Graphics_drawRectangle(&grContext, &rect);
    Graphics_setForegroundColor(&grContext, BORDER_FOCUSED_COLOR);
    Graphics_fillRectangle(&grContext, &rect);
    Graphics_Rectangle temp={rect.xMin+BORDER, rect.yMin+BORDER, rect.xMax-BORDER, rect.yMax-BORDER};
    Graphics_drawRectangle(&grContext, &temp);
    if (state==FOCUSED) {
        Graphics_setForegroundColor(&grContext, chooseColorRect(FOCUSED, color));
    }
    else {
        if (state==SELECTED) {
            Graphics_setForegroundColor(&grContext, chooseColorRect(SELECTED, color));
        }
    }
    Graphics_fillRectangle(&grContext, &temp);
}
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
int8_t findSelected(Graphics_Button array[], int8_t size) {
    int8_t i;
    for (i=0; i<size; i++) {
        if (array[i].state==SELECTED) {
            return i;
        }
    }
    return -1;
}
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
void drawButton(Graphics_Button button, int32_t rect_color, int32_t text_color, int8_t pos_selected) {
    if(button.state==FOCUSED || (button.state==SELECTED && position==pos_selected)) {
        focusedhandle(button.state, button.rect, rect_color);
    }
    else {
        Graphics_drawRectangle(&grContext, &button.rect);
        Graphics_setForegroundColor(&grContext, chooseColorRect(button.state, rect_color));
        Graphics_fillRectangle(&grContext, &button.rect);
    }
    Graphics_setForegroundColor(&grContext, chooseColorText(button.state, text_color));
    Graphics_drawStringCentered(&grContext, (int8_t *) button.text.string, AUTO_STRING_LENGTH, getCenteredX(button.rect),  getCenteredY(button.rect), button.text.opacity);

}
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
void rectangleWithText(Graphics_Rectangle rect, int32_t colorRect, Graphics_Text text, int32_t colorText) {
    if(colorRect!=-1) {
        Graphics_drawRectangle(&grContext, &rect);
        Graphics_setForegroundColor(&grContext, colorRect);
        Graphics_fillRectangle(&grContext, &rect);
    }
    Graphics_setForegroundColor(&grContext, colorText); //Manual
    Graphics_drawStringCentered(&grContext, (int8_t *)text.string, AUTO_STRING_LENGTH, getCenteredX(rect),  getCenteredY(rect), text.opacity);
}
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
void handleOut(Graphics_Button array[], uint8_t position, int8_t size) {
    if(display_position==GAME || display_position==CHRONOLOGY){
         if (array[position].state!=SELECTED) {
                array[position].state=STANDARD;
                drawButton(array[position], STANDARD_COLOR, SELECTED_COLOR, findSelected(array, size));
         }
          else {
                int output=findSelected(array, size)+1;//IN ORDER TO MAKE output!=position
                drawButton(array[position], SELECTED_COLOR, STANDARD_COLOR, output);
            }
    }
     else {
         if(position<(size-2)) {
                 if (array[position].state!=SELECTED) {
                     array[position].state=STANDARD;
                     drawButton(array[position], STANDARD_COLOR, SELECTED_COLOR, findSelected(array, size));
                 }
                 else {
                     int output=findSelected(array, size)+1;//IN ORDER TO MAKE output!=position
                     drawButton(array[position], SELECTED_COLOR, STANDARD_COLOR, output);
                 }
             }
             else {
                 array[position].state=STANDARD;
                 drawButton(array[position], FILL_MOVEMENT, STANDARD_COLOR, findSelected(array, size));
             }
    }
}
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
void handleIn(Graphics_Button array[], uint8_t position, int8_t size) {
    if (array[position].state!=SELECTED) {
        array[position].state=FOCUSED;
        drawButton(array[position], STANDARD_COLOR, BORDER_FOCUSED_COLOR, findSelected(array, size));
    }
    else {
        drawButton(array[position], SELECTED_COLOR, STANDARD_COLOR, findSelected(array, size));
    }
}
/**
 * @brief initializa all the hardware, including ports and interrupts
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void hardware_Init() {
    graphics_Init();
    configurePortsInput();
    configureInterruptPortInput();
    before_ADC();
    _adcInit();
}
/**
 * @brief handles the prev and next buttons
 * @param the buttons' array of the current interface
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handle_buttons(Graphics_Button array[]){
    if(position<(sizes[display_position]-2)){
        switch(display_position) {
            case DIMENSION: handlePressure_DIMENSION(); break;
            case DIFFICULTY: handlePressure_DIFFICULTY(); break;
            case TENTATIVE: handlePressure_TENTATIVE(); break;
            case DOUBLES: handlePressure_DOUBLES(); break;
            default: exit(1);
        }
    }
    else{
       if(position==(sizes[display_position]-2)){
           display_position--;
           position=0;
       }
       else {
           if(position==(sizes[display_position]-1)){
               display_position++;
               position=0;
               if(display_position==INFO) {
                   position=sizes[INFO]-1;
                   info_buttons[position]=nextButton;
               }
           }
       }
    }
}
/**
 * @brief selects the currently focused button
 * @param buttons' array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handleSelection(Graphics_Button array[]) {
    int i;
    for (i=0; i<sizes[display_position]; i++) {
        array[i].state=STANDARD;
    }
    array[position].state=SELECTED;
    position=sizes[display_position]-1;
    array[position].state=FOCUSED;
}
/**
 * @brief Resets all buttons to "STANDARD"
 * @param buttons' array
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void handleDeselection(Graphics_Button array[]) {
    int i;
    for (i=0; i<sizes[display_position]; i++) {
        array[i].state=STANDARD;
    }
    position=sizes[display_position]-1;
    array[position].state=DISABLED;
}
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
void initArray(Graphics_Button array[], int size) {
    if (position!=size-2) {
        array[size-2]=prevButton;
    }
    if (position!=size-1) {
        array[size-1]=nextButton;
    }
    if(findSelected(array, size)!=-1) {
        array[size-1].state=STANDARD;
    }
    if (position!=findSelected(array, size)) {
        array[position].state=FOCUSED;
    }
}
/**
 * @brief it activates the mutex
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void acquireMutex() {
    __disable_irq();
    if(!mutex) {
        mutex=true;
        __enable_irq();
    }
    __enable_irq();
}
/**
 * @brief it releases the mutex
 * @return void
 * @author Matteo Gottardelli (Primary author)
 * @author Niccolo Cristoforetti (Helper)
 * @author Daniele Calvo (Maintainer)
 * @date 2024-10-5
 */
void releaseMutex() {
    __disable_irq();
    mutex=false;
    __enable_irq();
    setupPriorities();
    ADC_EnableInterrupts();

}

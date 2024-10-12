/*
 * implementations.c
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "implementations.h"
#include "graphics.h"
#include "joystick.h"
#include "buttons.h"
#include "dimension.h"
#include "difficulty.h"
#include "tentatives.h"
#include "doubles.h"


void reset_Screen(void) {
    Graphics_setFont(&grContext, &g_sFontFixed6x8); //resets the font to the standard one, probably not necessary but anyways it's good practice to put it
    Graphics_setForegroundColor(&grContext, STANDARD_COLOR); //sets foreground to black
    Graphics_setBackgroundColor(&grContext, SELECTED_COLOR); //sets background to white for the borders
    Graphics_clearDisplay(&grContext);
}
void graphics_Init(void) {
    //INITIALIZE DISPLAY AND DRIVERS
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    Graphics_initContext(&grContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setFont(&grContext, &g_sFontFixed6x8);
    reset_Screen();
}
int32_t getCenteredX(Graphics_Rectangle rect) {
    return (rect.xMax+rect.xMin)/2;
}
int32_t getCenteredY(Graphics_Rectangle rect) {
    return (rect.yMax+rect.yMin)/2;
}
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
int8_t findSelected(Graphics_Button array[], int8_t size) {
    int8_t i;
    for (i=0; i<size; i++) {
        if (array[i].state==SELECTED) {
            return i;
        }
    }
    return -1;
}
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
void defaultDraw(void) {
    //START LABEL
    if(display_position==DIMENSION || display_position==DIFFICULTY || display_position==TENTATIVE || display_position==DOUBLES || display_position==INFO){
        Graphics_drawRectangle(&grContext, &upperRect);
        Graphics_setForegroundColor(&grContext, FILL_UPPER_RECT);
        Graphics_fillRectangle(&grContext, &upperRect);
        Graphics_setForegroundColor(&grContext, GRAPHICS_COLOR_WHITE); //Manual
        Graphics_drawStringCentered(&grContext, (int8_t *)labelText.string, AUTO_STRING_LENGTH, getCenteredX(upperRect),  getCenteredY(upperRect), labelText.opacity);
    }
}
void handleOut(Graphics_Button array[], uint8_t position, int8_t size) {
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
void handleIn(Graphics_Button array[], uint8_t position, int8_t size) {
    if (array[position].state!=SELECTED) {
        array[position].state=FOCUSED;
        drawButton(array[position], STANDARD_COLOR, BORDER_FOCUSED_COLOR, findSelected(array, size));
    }
    else {
        drawButton(array[position], SELECTED_COLOR, STANDARD_COLOR, findSelected(array, size));
    }
}
void hardware_Init() {
    before_ADC();
    graphics_Init();
    _adcInit();
    button_Init();
}

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
           }
       }
    }
}
void handleSelection(Graphics_Button array[]) {
    int i;
    for (i=0; i<sizes[display_position]; i++) {
        array[i].state=STANDARD;
    }
    array[position].state=SELECTED;
    position=sizes[display_position]-1;
    array[position].state=FOCUSED;

}
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
void fn_GAME(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_CHRONOLOGY(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_END(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}

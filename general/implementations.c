/*
 * implementations.c
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "implementations.h"
#include "graphics.h"
#include "joystick.h"

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
        case FOCUSED: c=color; break;
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
void focusedhandle(Graphics_Rectangle rect, int32_t color) {
    Graphics_drawRectangle(&grContext, &rect);
    Graphics_setForegroundColor(&grContext, BORDER_FOCUSED_COLOR);
    Graphics_fillRectangle(&grContext, &rect);
    Graphics_Rectangle temp={rect.xMin+BORDER, rect.yMin+BORDER, rect.xMax-BORDER, rect.yMax-BORDER};
    Graphics_drawRectangle(&grContext, &temp);
    Graphics_setForegroundColor(&grContext, chooseColorRect(FOCUSED, color));
    Graphics_fillRectangle(&grContext, &temp);
}
void drawButton(Graphics_Button button, int32_t rect_color, int32_t text_color) {
    if(button.state==FOCUSED) {
        focusedhandle(button.rect, rect_color);
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
void hardware_Init() {
    before_ADC();
    graphics_Init();
    _adcInit();
    //BUTTONS INIT
}
void fn_START_GR(void) {
    //DRAW FUNCTION
    //FOLLOWING POSITION
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

/*
 * implementations.c
 *
 *  Created on: 5 ott 2024
 *      Author: matteogottardelligmail.com
 */
#include "implementations.h"
#include "graphics.h"
void reset_Screen() {
    Graphics_setForegroundColor(&grContext, FOREGROUND_STANDARD_COLOR);
    Graphics_setBackgroundColor(&grContext, BACKGROUND_STANDARD_COLOR);
    Graphics_clearDisplay(&grContext);
}
void graphics_Init() {
    //INITIALIZE DISPLAY AND DRIVERS
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    Graphics_initContext(&grContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setFont(&grContext, &g_sFontFixed6x8);
}
void hardware_Init() {
    graphics_Init();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_START_GR(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_DIMENSION(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_DIFFICULTY(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_TENTATIVE(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_DOUBLES(void) {
    reset_Screen();
    //DRAW FUNCTION
    //FOLLOWING POSITION
}
void fn_INFO(void) {
    reset_Screen();
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

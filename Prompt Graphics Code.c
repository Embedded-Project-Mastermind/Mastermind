#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <stdbool.h>

//0. SETUP ENVIRONMENT
/* Search the four files sent on Whatsapp and save them in a folder called LcdDriver
 * Create a project CCS and setup the machine for MSP432P401R
 * Add the folder previously created in the project 
 * Download and install simplelink for mps432 on ti.com, based on your OS
 * Go on the properties right-clicking on the created project
 * In the left column select Build > Arm Compiler > Include Options
 * In add dir to #include search path click the add file icon and then Browse
 * Search the simplelink_msp432p4_sdk_3_40_01_02 folder. If you can't find it, go on Applications > ti
 * In this folder follow this path simplelink_msp432p4_sdk_3_40_01_02 > source and click on open and then OK
 * Then, always in the left column select Build > Arm Linker > File Search Path
 * In include library file or command file as input click the add file icon and then Browse
 * You will have to do this twice with two different paths, but first search the simplelink folder:
 * 1. simplelink_msp432p4_sdk_3_40_01_02 > source > ti > devices > mps432p4xx > driverlib > ccs > msp432p4xx_driverlib.lib
 * 2. simplelink_msp432p4_sdk_3_40_01_02 > source > ti > grlib > lib > ccs > m4 > grlib.a
 * After adding the files successfullt, click bottom-right apply and close
 * Finally, rebuild the project and try to check out if this file pasted in main.c generates errors
 */

//1. DEFINITION OF CONTEXT
Graphics_Context grContext;
//2. DEFINITION OF COLORS

//BACKGROUND COLORS
const int32_t BACKGROUND_COLOR=GRAPHICS_COLOR_BLACK;
const int32_t RECT_SELECTED=GRAPHICS_COLOR_WHITE;

//FOREGROUND COLORS
const int32_t FOREGROUND_COLOR=GRAPHICS_COLOR_WHITE;
const int32_t TEXT_SELECTED=GRAPHICS_COLOR_BLACK;

/*3. THIS IMPLEMENTATION AS TO BE DONE IF THE CHANGE OF THE ELEMENTS CHANGE, IF THEIR STATE DOESN'T CHANGE DO A SEPARATE DECLARATION WITHOUT ARRAY*/

//IMPLEMENTATION GROUPS (List of strings, rectangles, circle, image).
/*EXAMPLE STRINGS
 * 1. Strings are 8 bit long so is direct
 * int8_t* menuOptions[]={
     *  "Option1",
     *  "Option2",
     *  "Option3",
     *  "Exit"
 *  };
 *  But if we would like we can create a struct, so
 *  typedef struct Graphics_Text {
 *      int8_t *string,
 *      int32_t x,
 *      int32_t y,
 *      bool opacity //1 opaque, 0 not opaque
 *  };
 *  Graphics_Text* menuOptions[]={
 *      {"Option1", x, y, 1},
 *      ... /others
 *  }
 *  EXAMPLE RECTANGLES
 *  Rectangles object are already defined
 *  This is the implementation predefined
 *
 *  typedef struct Graphics_Rectangle
{
    int16_t xMin;              //!< The minimum X coordinate of the rectangle.
    int16_t yMin;            //!< The minimum Y coordinate of the rectangle.
    int16_t xMax;            //!< The maximum X coordinate of the rectangle.
    int16_t yMax;            //!< The maximum Y coordinate of the rectangle.
} Graphics_Rectangle;
 *
 *  Is only for reference!!! Not implement this struct
 *
 *  Graphics_Rectangle* menuRectangle[]={
      {xMin, yMin, xMax, yMax} //Rect 1
      ... //Others
};
 * EXAMPLE CIRCLES
 *
 * The struct is not defined so, if you use you have to put at the start of this file
 * typedef struct Graphics_Circle {
 *   int32_t x; //Center coordinate x
 *   int32_t y; //Center coordinate y
 *   int32_t radius; //Length in bit
 * } Graphics_Circle;
 *
 * Graphics_Circle* menuCircles[]={
 *      {50, 50, 5}, //Circle 1
 *      ... //Others
 * };
 *
 * EXAMPLE IMAGE
 *
 * The struct is already implemented, this is its definition
 * typedef struct Graphics_Image
    {
        uint8_t bPP;                 //!< Bits per pixel and Compressed/Uncompressed
        uint16_t xSize;              //!< xSize
        uint16_t ySize;              //!< ySize
        uint16_t numColors;          //!< Number of Colors in Palette
        const uint32_t  * pPalette;  //!< Pointer to Palette
        const uint8_t * pPixel;      //!< Pointer to pixel data;
    } Graphics_Image;

 *  bPP uses a constant defined in grlib.h based on bits per pixel (see that file to view them)
 *   pPalette and pPixel refers one on the options of colors, the second on the data of each bit.
 *
 *  BUTTONS
 *
 *  The struct is not implemented as Circle, but the functions have to be created too, so its better
 *  to handle these elements with a rectangle or circle combined with a text, but can be threated as separate. Here are the two implementations:
 *  typedef struct Graphics_Button_Rect {
 *      Graphics_Rectangle rect;
 *      int8_t text;
 *  } Graphics_Button_Rect;
 *
 *  Graphics_Button_Rect* menuButtons[]={
 *      {{xMin, yMin, xMax, yMax}, "Option1"}
 *  }
 *  Design choice has to be taken
 */
/*4. Selected index (only one element can be selected an it is determined by this variable)
 *Preferable that all the elements that can be pressed in the page are same types in the array.
 *Example if selected Option=0 and we have two array one of texts and one of rectangles,
 *the first elements of each array will be selected.
*/
int selectedOption=0;
//5. Dimension of the arrays can be calculated with this formula
//int numOptions=sizeof(array)/sizeof(array[0]);
int numOptions=3; //To change
//6. Drawing elements time (Release Your Freedom)
void drawMenu() {
    Graphics_setForegroundColor(&grContext, FOREGROUND_COLOR);
    Graphics_setBackgroundColor(&grContext, BACKGROUND_COLOR);
    Graphics_clearDisplay(&grContext);
    //int i;
    //for (int i=0; i<numOptions; i++) {
        /* Trying to draw the elements with a reuse of code
         *
         * RECTANGLES AND CIRCLES
         *
         * With rectangle and circle the functions are easy
         * RECT: Graphics_drawRectangle(&grContext, menuRect[i]);
         * CIRC: Graphics_drawCircle (&grContext, menuCircle[i].x, menuCircle[i].y, menuCircle[i].radius);
         * Remember before set desired Foreground Color, then draw
         * For RECT and CIRC with only drawing won't will the content, but will only color the border
         * In order to fill the two figures, set the desired foreground color, that can be different from the one before
         * and then compute the functions:
         * RECT: Graphics_fillRectangle with the same parameters of the one above
         * CIRCLE: Graphics_fillCircle with the same parameters of the one above
         *
         * TEXTS
         *
         * The texts doesn't have a fill function, when the draw function is called they are colored with the set foreground color,
         * so first set the foreground color
         * The function to draw the element
         * Graphics_drawString(&grContext, menuOptions[i], -1 (length of word, with -1 print all the word up to /0), x, y, opacity);
         * Based on the implementation adopted above
        */
    //}
}
//7. Default Graphical Initialization Function Don't touch
void graphicsInit()
{
    //INITIALIZE DISPLAY AND DRIVERS
    Crystalfontz128x128_Init();
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    Graphics_initContext(&grContext, &g_sCrystalfontz128x128, &g_sCrystalfontz128x128_funcs);
    Graphics_setFont(&grContext, &g_sFontFixed6x8);
    drawMenu();
}
//8. Main Definition
int main(void) {
    WDT_A_holdTimer();
    graphicsInit();
    while(1) {
        __sleep();
    }
}
//FINAL TIPS
// 1.  Trying the compilation sometimes there is an error in functions invocation, especially with array elements, so do a cast if that is the case
// 2. If a function is declared in a library it will be cyan, typically with Graphics functions
// 3. Try to implement a logical an symmetric in order that is accessible by the joystick with four directions in order to be intuitive in future
// implementation, so for example all elements in row, column, or in square disposal

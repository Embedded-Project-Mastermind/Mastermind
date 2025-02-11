/*
 * Title: chronology.h
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: Matteo Gottardelli
 * Maintainability: Niccolò Cristoforetti, Matteo Gottardelli
 * Date Creation: 31 ott 2024
 */
#include "chronology.h"
#include "implementations.h"
#include "graphics.h"
#include "fsm.h"
#include "joystick.h"
#include "game.h"
#include "gamelogic1.h"
#include "string.h"

/**
 * @brief function that create buttons and text for the Chronology screen
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void drawChronology(void) {
    Graphics_Button return_to={STANDARD, {128-16+1, 1, 128-1, 16-1}, {"->", false}};
    int i;
    for (i=0; i<sizes[CHRONOLOGY]; i++) {
        drawButton(chronology[i].button, STANDARD_COLOR, SELECTED_COLOR, -1);
        rectangleWithText(chronology[i].num_rect, SELECTED_COLOR, chronology[i].num, STANDARD_COLOR);

        if(chronology[i].button.state!=DISABLED){
            drawCircles(chronology[i].chrono_circles);
            drawPastResults(chronology[i].chrono_buttons);
        }
    }
  for (i=0; i<2; i++) {
        drawButton(other_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, -1);
    }
    drawButton(return_to, GRAPHICS_COLOR_CYAN, STANDARD, findSelected(&return_to, 1));
}

/**
 * @brief functions that create the Chronology screen starting from resetting the previous screen
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void fn_CHRONOLOGY(void) {
    int i;
    //DRAW FUNCTION
    reset_Screen();
    if(game.count_tent-1>=pos_chronology+sizes[CHRONOLOGY]){
        other_buttons[1].state=STANDARD;
    }
    for (i=0; i<sizes[CHRONOLOGY] && i<game.count_tent; i++) {
          chronology[i].button.state=STANDARD;
    }
    chronology[position].button.state=FOCUSED;
    rectangleWithText((Graphics_Rectangle){upperRect.xMin, upperRect.yMin, upperRect.xMax, upperRect.yMax-16}, FILL_UPPER_RECT, labelText, SELECTED_COLOR);

    updatePos();
    drawChronology();

}

/**
 * @brief converts the number associated to the color to its color char
 * @param integer
 * @return char
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
int16_t char_Conversion_to_Int(int8_t index) {
    int16_t c=0;
    switch (index) {
        case 'R': c = 1; break; // Red
        case 'G': c = 2; break; // Green
        case 'B': c = 3; break; // Blue
        case 'Y': c = 4; break; // Yellow
        case 'P': c = 5; break; // Purple
        case 'C': c = 6; break; // Cyan
        case 'O': c = 7; break; // Orange
        case 'W': c = 8; break; //White
        default: exit(1); // Exit on error
    }
    return c; // Return the character representation
}
/**
 * @brief populate the cHronology circle with their colors
 * @param radius dimension of the circle
 * @param value position of the sequence
 * @param index that indicates History of attempts
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void populateChronologyCircles(int16_t radius, int16_t value, int16_t index){
    int j;
    for (j=0; j<game.dim; j++) {
        chronology[value].chrono_circles[j].radius=radius;
        chronology[value].chrono_circles[j].x= (128/(game.dim+1))*(j+1);
        chronology[value].chrono_circles[j].y=47*value+46;
        int16_t tmp = char_Conversion_to_Int(game.chronology[index*game.dim*2+j]);
        chronology[value].chrono_circles[j].color=selectColor(tmp);
    }
}
/**
 * @brief function that populate chronology buttons
 * @param value position of the sequence
 * @param index that indicates History of attempts
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void populateChronologyButtons(int16_t value, int16_t index){
    int i;
    for (i=0; i<game.dim; i++) {
            if(chronology[value].chrono_buttons[i].text.string!=NULL){
                free(chronology[value].chrono_buttons[i].text.string);
            }
            chronology[value].chrono_buttons[i].text.string=(int8_t*)malloc(2*sizeof(int8_t));
            if(chronology[value].chrono_buttons[i].text.string==NULL){
                printf("Memory allocation failed!\n");
                emergency();
                exit(1);
            }
            char str[2]={game.chronology[index*game.dim*2+game.dim+i], '\0'};
            strcpy((char*)chronology[value].chrono_buttons[i].text.string, (char*)str);
            chronology[value].chrono_buttons[i].text.string[1]='\0';
            chronology[value].chrono_buttons[i].rect=(Graphics_Rectangle){
                        (128/(game.dim+1))*(i+1)-RADIUS, 47*value+57,
                                (128/(game.dim+1))*(i+1)+RADIUS, 47*value+67
                        };
        }
}

/**
 * @brief TODO: Describe function.
 * @param buttons TODO: Describe parameter.
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void drawPastResults(Graphics_Button* buttons){
    int i;
    for (i=0; i<game.dim; i++) {
        printf("\n STRINGA %s ", buttons[i].text.string);
        Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
        Graphics_setFont(&grContext, &g_sFontFixed6x8);
        rectangleWithText(buttons[i].rect,-1,buttons[i].text,SELECTED_COLOR); //non disegna il testo e qua non so se ci vada il -1 perchè piu che altro senno salta mezza funzione
   }

}

/**
 * @brief manage what to do when the user moves the stick up
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void upStick_CHRONOLOGY() {
    if(position!=0) {
        chronology[position].button.state=STANDARD;
        position--;
        chronology[position].button.state=FOCUSED;
    }
    else if(position==0 && other_buttons[0].state==STANDARD){
        pos_chronology--;
        position=0;
        if(pos_chronology==0){
            other_buttons[0].state=DISABLED;
        }
        if(game.count_tent-1>pos_chronology+sizes[CHRONOLOGY]){
            other_buttons[1].state=STANDARD;
        }
        //Modified previous screens
        updatePos();
    }
}
/**
 * @brief manage what to do when the user moves the stick down
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void downStick_CHRONOLOGY() {
    if(position<game.count_tent-1) {
        if(position<sizes[CHRONOLOGY]-1) {
            chronology[position].button.state=STANDARD;
            position++;
            chronology[position].button.state=FOCUSED;
        }
        else if(position==sizes[CHRONOLOGY]-1 && other_buttons[1].state==STANDARD) {
            pos_chronology++;
            position=sizes[CHRONOLOGY]-1;
            chronology[position].button.state=FOCUSED;
            if(pos_chronology>0) {
                other_buttons[0].state=STANDARD;
            }
            if(game.count_tent<=pos_chronology+sizes[CHRONOLOGY]){
                other_buttons[1].state=DISABLED;
            }
            //Modified previous screens
            updatePos();
        }
    }
}
/**
 * @brief manage what to do when the user moves the stick right
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void rightStick_CHRONOLOGY() {
    display_position--;
    configurationGame=true;
}

/**
 * @brief show the last attempts of the chronology or the ones that were selected by the joystick
 * @return void
 * @author Niccolò Cristoforetti (Primary Author & Maintainer)
 * @author Matteo Gottardelli (Helper & Maintainer)
 * @date 2024-10-31
 */
void updatePos(){
        int i, j;
        for (i=0; i<sizes[CHRONOLOGY]; i++){
            if (chronology[i].button.state!=DISABLED) {
                int16_t result=game.count_tent-i-pos_chronology;
                if(result>0) {
                    char buffer[20];
                    char* str=ltoa((long)result, buffer, 10);
                    deallocate_Char(chronology[i].num.string);
                    chronology[i].num.string = (int8_t*)malloc(strlen(str) + 1);
                    if (chronology[i].num.string == NULL) {
                        printf("Memory allocation failed!\n");
                        emergency();
                        exit(1);
                    }
                    for (j=0; str[j]!='\0'; j++){
                        chronology[i].num.string[j] = (int8_t)str[j];
                    }
                    chronology[i].num.string[strlen(str)] = '\0';
                    printf("Chronology[%d] num.string: %s %s\n", i, str, chronology[i].num.string);
                    populateChronologyCircles(RADIUS,i, result-1);
                    populateChronologyButtons(i, result-1);
                }
            }
        }
}

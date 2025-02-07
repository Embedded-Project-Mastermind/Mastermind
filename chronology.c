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

/***************************************
*
* drawChronology() - function that create
* buttons and text for the Chronology screen
* no input
* no output
*
***************************************/

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
    //non riesco a centare il testo
    //Graphics_drawStringCentered(&grContext, (int8_t *) chronology[i].num.string, AUTO_STRING_LENGTH, getCenteredX(chronology[i].num_rect),  getCenteredY(chronology[i].num_rect), chronology[i].num.opacity);
    for (i=0; i<2; i++) {
        drawButton(other_buttons[i], FILL_MOVEMENT, STANDARD_COLOR, -1);
    }
    drawButton(return_to, GRAPHICS_COLOR_CYAN, STANDARD, findSelected(&return_to, 1));
}

/***************************************
*
* fn_CHRONOLOGY() - functions that create
* the Chronology screen starting from
* resetting the previous screen
* no input
* no output
*
***************************************/


void fn_CHRONOLOGY(void) {
    int i;
    //DRAW FUNCTION
    reset_Screen();
    if(game.count_tent-1>=sizes[CHRONOLOGY]){
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

void populateChronologyCircles(int16_t offset, int16_t radius, int16_t value, int16_t index){
    int j;
    for (j=0; j<game.dim; j++) {
        chronology[value].chrono_circles[j].radius=radius;
        /*if(j<3){
            chronology[value].chrono_circles[j].x= offset+(58/3)*j;
            chronology[value].chrono_circles[j].y=32*value+35;
            //chronology[value].chrono_circles[j].y=47*value+43; //con 2 lo sfaso dovrebbe essere di 47 pixel, vedi il main dove sono dichiarati i componenti della schermata chronology
        } else {
            chronology[value].chrono_circles[j].x= offset+(58/3)*(j-2);
            chronology[value].chrono_circles[j].y=32*value+45;
            //chronology[value].chrono_circles[j].y=47*value+45;
        }*/

        chronology[value].chrono_circles[j].x= (128/(game.dim+1))*(j+1);
        chronology[value].chrono_circles[j].y=47*value+46;
        //chronology[value].chrono_buttons[j].x=(128/(game.dim+1))*(j+1); Sbagliato, sottrarre il raggio e alzarlo dato che dobbiamo prendere l'angolo in alto a sinistra e quello in basso a destra
        //chronology[value].chrono_buttons[j].y=47*value+46;

        int16_t tmp = char_Conversion_to_Int(game.chronology[index*game.dim*2+j]);
        chronology[value].chrono_circles[j].color=selectColor(tmp);
    }
}

void populateChronologyButtons(int16_t value, int16_t index){
    int i;
    for (i=0; i<game.dim; i++) {
            if(chronology[value].chrono_buttons[i].text.string!=NULL){
                free(chronology[value].chrono_buttons[i].text.string);
                chronology[value].chrono_buttons[i].text.string=NULL;
            }
            if(chronology[value].chrono_buttons[i].text.string==NULL){
                chronology[value].chrono_buttons[i].text.string=(int8_t*)malloc(2*sizeof(int8_t));
            }

            printf("\n 1 ");

            if(chronology[value].chrono_buttons[i].text.string==NULL){
                printf("Memory allocation failed!\n");
                emergency();
                exit(1);
            }
            printf(" 2 ");

            strcpy((char*)chronology[value].chrono_buttons[i].text.string, (char*)&game.chronology[index*game.dim*2+game.dim+i]);

            //memmove(chronology[value].chrono_buttons[i].text.string, &game.chronology[index*game.dim*2+game.dim+i], sizeof(int8_t));
            chronology[value].chrono_buttons[i].text.string[1]='\0';
            //strcpy((char*)chronology[value].chrono_buttons[i].text.string, str);



            /*switch(str[0]){
               case '!': chronology[value].chrono_buttons[i].text.string[0]='!'; break;
               case 'O': chronology[value].chrono_buttons[i].text.string[0]='O'; break;
               case 'X': chronology[value].chrono_buttons[i].text.string[0]='X'; break;
               default: exit(1);
           }*/
            printf(" pop %s ", chronology[value].chrono_buttons[i].text.string);
            chronology[value].chrono_buttons[i].rect=(Graphics_Rectangle){
                        /*chronology[value].chrono_circles[i].x - chronology[value].chrono_circles[i].radius,
                        chronology[value].chrono_circles[i].y + chronology[value].chrono_circles[i].radius + 6,
                        chronology[value].chrono_circles[i].x + chronology[value].chrono_circles[i].radius,
                        chronology[value].chrono_circles[i].y + chronology[value].chrono_circles[i].radius + 6 + 8*/
                        (128/(game.dim+1))*(i+1)-RADIUS, 47*value+57,
                                (128/(game.dim+1))*(i+1)+RADIUS, 47*value+67
                        };
        }
}


void drawPastResults(Graphics_Button* buttons){
    int i;
    for (i=0; i<game.dim; i++) {
        printf("\n STRINGA %s ", buttons[i].text.string);

        Graphics_setForegroundColor(&grContext, SELECTED_COLOR);
       // Graphics_fillCircle(&grContext, chronology[value].chrono_circles[i].x, chronology[value].chrono_circles[i].y+6, chronology[value].chrono_circles[i].radius);
     //   int8_t str[2]={game.chronology[index*game.dim*2+game.dim+i], '\0'};
        Graphics_setFont(&grContext, &g_sFontFixed6x8);
        /*rectangleWithText(
            (Graphics_Rectangle){
            chronology[value].chrono_circles[i].x - chronology[value].chrono_circles[i].radius,
            chronology[value].chrono_circles[i].y - chronology[value].chrono_circles[i].radius + 6,
            chronology[value].chrono_circles[i].x + chronology[value].chrono_circles[i].radius,
            chronology[value].chrono_circles[i].y + chronology[value].chrono_circles[i].radius + 6
            },
            -1,
            (Graphics_Text){str, false},
            STANDARD_COLOR
        );*/
        rectangleWithText(buttons[i].rect,-1,buttons[i].text,SELECTED_COLOR); //non disegna il testo e qua non so se ci vada il -1 perch� piu che altro senno salta mezza funzione
   }

}

/***************************************
*
* upStick_CHRONOLOGY() / douwnStick_CHRONOLOGY() / rightStick_CHRONOLOGY()
* they manage what to do when the user
* moves the stick
* no input
* no output
*
***************************************/

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
        //Modifica le schermate precedenti
        updatePos();
    }
}
void downStick_CHRONOLOGY() {
    if(position<sizes[CHRONOLOGY]-1) {
        chronology[position].button.state=STANDARD;
        position++;
        chronology[position].button.state=FOCUSED;
    }
    else if(position==sizes[CHRONOLOGY]-1 && other_buttons[1].state==STANDARD) {
        pos_chronology++;
        position=sizes[CHRONOLOGY]-1;
        chronology[position].button.state=FOCUSED;
        if(game.count_tent-1<=pos_chronology+sizes[CHRONOLOGY]){
            other_buttons[1].state=DISABLED;
        }
        if(pos_chronology>0) {
            other_buttons[0].state=STANDARD;
        }
        //Modifica le schermate precedenti
        updatePos();
    }
}
void rightStick_CHRONOLOGY() {
    display_position--;
    configurationGame=true;
}
/***************************************
*
* updatePos()
* they manage what to do when the user
* moves the stick
* no input
* no output
*
***************************************/

void updatePos(){
        int i, j;
        for (i=0; i<sizes[CHRONOLOGY]; i++){
            if (chronology[i].button.state!=DISABLED) {
                int16_t result=game.count_tent-i-pos_chronology;
                if(result>0) {
                    char buffer[20];
                    char* str=ltoa((long)result, buffer, 10);
                    if(chronology[i].num.string!=NULL){
                                   free(chronology[i].num.string);
                    }
                    printf("3");
                    chronology[i].num.string = (int8_t*)malloc(strlen(str) + 1);
                    if (chronology[i].num.string == NULL) {
                        printf("Memory allocation failed!\n");
                        emergency();
                        exit(1);
                    }
                    printf("4");
                    for (j=0; str[j]!='\0'; j++){
                        chronology[i].num.string[j] = (int8_t)str[j];
                    }
                    chronology[i].num.string[strlen(str)] = '\0';
                    printf("Chronology[%d] num.string: %s %s\n", i, str, chronology[i].num.string);
                    populateChronologyCircles(BASIC_OFFSET,RADIUS,i, result-1);
                    populateChronologyButtons(i, result-1);
                }
            }
        }
}

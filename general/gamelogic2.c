/*
 * Title: gamelogic2.c
 * Primary Authors: Alessandro Benassi, Daniele Calvo
 * Helpers: Matteo Gottardelli
 * Maintainability: Alessandro Benassi, Daniele Calvo
 * Date Creation: 27 set 2024
 */
#include "gamelogic2.h"
#include "game.h"
//For avoiding duplicates in compilation
int8_t temp;
int16_t value;
bool selection;

/**
 * @brief returns if the user’s sequence is empty or not
 * @return boolean
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
bool is_empty(void){ 
     return (tentative.count == 0);
}

/**
 * @brief returns if the user’s sequence is full or not
 * @return boolean
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
bool is_full(void){
     return (tentative.count  == tentative.dim);
}

/**
 * @brief (Outdated) it was the main menu for the logic test on console
 * @param a boolean to switch from two distinct menu
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void text_selection(bool sel){     //selects which text to display
    if(sel){             //if true -> button menu
    printf("Selection menu: \n- Type 1 to insert an input \n- Type 2 to press confirm\n- Type 3 to press back \nSelection: ");
    }
    else{             //if false -> color menu
        printf("Colors selection menu:\n- 1 red \n- 2 green \n- 3 blue \n-4 yellow \n- 5 purple \n- 6 cyan \nSelection: ");
    }
}

/**
 * @brief (Outdated) print to indicate the full state of the array on console
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void full_text(){
     printf("The array is full, click 2 to confirm and 3 to go back.\nSelection: ");    
}
/*
int read_input(int16_t dim){     //reads the input from keyboard and verifies if it's correct
    int16_t value = 0;
    do{       //done with a do while so we are sure that it executes
       if(current_state == WAIT || current_state == ELABORATE) { text_selection(selection);}
       else if(current_state == WAIT_FULL) { full_text(); }    

       //

       scanf("%d", &value);       //scans the value to analize
       if(selection && ((current_state == WAIT && value == 2) || (current_state == WAIT_FULL && value == 1) || (is_empty() && value == 3))){
           printf("Function not available in this state!");
           value = 0;
       }
       }while(value < 1 || value > dim);    //do while exit condition
    return value;
}*/

/**
 * @brief (Outdated) print on console of the user's sequence
 * @param a pointer to the sequence
 * @param the dimension of the array for the user's sequence
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void print_sequence(int8_t* seq, int16_t dim){
     for(i=0; i<dim; i++){
             printf("%c ", seq[i]);
             }
     printf("\n");
}
/*
void handle_wait(int16_t value){ //potenzialmente inutile
    switch(value){
        case 1: current_state  = ELABORATE;
            break;
        case 2: current_state = ELABORATE_TENT;
            break;
        case 3: current_state = ELIMINATE_COLOR;
            break;
        default: exit(1);
    }
}*/
/*
void wait_handle(void) { 
     selection = true;      //to select menu text from text_selection()
     value = read_input(OPTIONS);       //to read the value in input
     selection = false;     //to change text selection in function text_selection
}*/
/*
void wait_full(void) {  //wait function when the array is full
    full_text();   //prints the text that tells what instructions you can do
//not useful    value = read_input(OPTIONS);   //gets the value from the keyboard
}*/


/**
 * @brief inserts the selected color into the user's sequence if space is available
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void insert_color(){
    if(!(is_full())){
        tentative.seq_user[tentative.count]=int_Conversion_to_Char(color_selected);
        circles[tentative.count].color=selectColor(color_selected);
        tentative.count +=1;
        fn_GAME();
    }
    else
        printf("array pieno!");
    print_sequence(tentative.seq_user, tentative.count);
}

/**
 * @brief deletes the last color into the user's sequence if it is not empty
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void eliminate_color(void){
     if(!(is_empty())){
     tentative.count -= 1;
     tentative.seq_user[tentative.count]= '\0';
     circles[tentative.count].color=STANDARD_COLOR;
     fn_GAME();
    }
     printf("color eliminated");
     print_sequence(tentative.seq_user, tentative.count);
}

/* 
bool elaborate(void){  
     selection = false;   //set boolean variable selection to false to display the correct text
     value = read_input(COLORS);   //gets input from keyboard as an integer
    // temp = int_Conversion_to_Char(value); //global variable that saves the chosen color
     return true;    //fittizio
}
*/

/**
 * @brief state while he's waiting an input
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_WAIT(void) {
//  wait_handle();  //actions of wait state
//  handle_wait(value);     //calls handle_wait(), which handles the input and redirects to the correct state
}
/**
 * @brief state for when he received an input (now useless)
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_ELABORATE(void){ //da rimuovere
/*  if(elaborate()){ current_state = INSERT_COLOR; }
    else { current_state = WAIT; }*/
    //current_state = (elaborate()) ? INSERT_COLOR : WAIT;  //if the input is correct it changes state to insert the color, otherwise returns to wait
}
/**
 * @brief state for inserting the color choosen by the user in its sequence
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_INSERT_COLOR(void){
    insert_color();  // calls insert_color(char color) function
 //verifies if the array is full or not and based on that decides in which state to jump
    current_state = (is_full()) ? WAIT_FULL : WAIT;
/*  if(is_full()){ current_state= WAIT_FULL;}
    else { current_state= WAIT; }*/
}
/**
 * @brief state while he's waiting an input with the user's sequence full
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_WAIT_FULL(void) {
//  wait_full(); //actions of wait_full state
//  handle_wait(value);     //calls handle_wait(), which handles the input and redirects to the correct state
}
/**
 * @brief state for deleting the last color of the user's sequence
 * @return void
 * @author Alessandro Benassi & Daniele Calvo (Primary Author)
 * @author Matteo Gottardelli (Helper)
 * @author Alessandro Benassi & Daniele Calvo (Maintainer)
 * @date 2024-09-27
 */
void fn_ELIMINATE_COLOR(void){
    eliminate_color();   //calls function eliminate_color
    current_state= WAIT;  //changes the current_state to WAIT
}

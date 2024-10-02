#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "fsm.h"
#include "gamelogic1.h"
#include "gamelogic2.h"

bool is_empty(void){     //tentative.count=null, then the array is empty (true, if not empty false) 
     (tentative.count = 0) ? true : false; 	
}

bool is_full(void){   	//If count=dim, then array is full (true, if != then false)
(tentative.count  = tentative.dim) ? true : false;
}

void text_selection(bool sel){     //selects which text to display
	if(sel){             //if true -> button menu
	printf("Selection menu: \n- Type 1 to insert an input \n- Type 2 to press confirm\n- Type 3 to press back \n");
	}
	else{             //if false -> color menu
		printf("Colors selection menu:\n- 1 red \n- 2 green \n- 3 blue \n-4 yellow \n- 5 purple \n- 6 cyan \n ");
	}
}

void full_text(){
     printf("The array is full, click 2 to confirm and 3 to go back");    
}

int read(int dim){     //reads the input from keyboard and verifies if it's correct
    int value = 0;
    do{       //done with a do while so we are sure that it executes
	   text_selection(selection);  //da mettere all'esterno se non vogliamo che ristampi il testo ogni volta(poco rilevante)
       value = scanf("%d", value);       //scans the value to analize
       if(value> 0 && value <= dim){     //value must respect these constraints
	             return value;
       }
       }while(value < 1 || value > dim);	//do while exit condition
}

void handle_wait(int val){
     if(current_state == WAIT){ text_selection(selection);}
     if(current_state == WAIT_FULL) { full_text(); }
	switch(val){
		case 1: if(current_state == WAIT){  
					current_state  = ELABORATE;}
				else{
					printf("Can't continue!");   //error message
				}
				break;
		case 2:	if(current_state == WAIT_FULL){
					current_state = ELABORATE_TENT;
				}
				else {
					printf("Can't elaborate because the array is not full!");  //error message
				}
				break;
		case 3: if(!is_empty()){
					current_state = ELIMINATE_COLOR;
				}
				else {
					printf("Can't eliminate color, because the array is empty");        //error message
				}
		default: exit(1);
	}
}

void wait() { 
     selection = true;  //to select menu text from text_selection()
     value = read(OPTIONS);   //to read the value in input
     selection = false;   //to change text selection in function text_selection
     handle_wait(value); //
	
}

void wait_full() {  //wait function when the array is full
    full_text();   //prints the text that tells what instructions you can do
	int value = read(OPTIONS);   //gets the value from the keyboard
	handle_wait(value);
}

void insert_color(char color){
	if(!(is_full())){
        tentative.seq_user[tentative.count]=color; 
        tentative.count +=1;
    }
}


void eliminate_color( ){  //eliminates color in position tentative.count from seq_user array
     if(!(is_empty())){
     tentative.count -= 1;   //decrements tentative.count
     tentative.seq_user[tentative.count]= '\0';   //eliminate color 
	}
	
}

bool elaborate(){  
     selection = false;   //set boolean variable selection to false to display the correct text
     value = read(COLORS);   //gets input from keyboard as an integer
     temp = int_Conversion_to_Char(value); //global variable that saves the chosen color
     return true; //fittizio
}
void fn_WAIT(void) {
	wait(); //actions of wait state
}

void fn_ELABORATE(void){
/*	if(elaborate()){ current_state = INSERT_COLOR; }
	else { current_state = WAIT; }*/
	current_state = (elaborate()) ? INSERT_COLOR : WAIT;
}

void fn_INSERT_COLOR(){
	insert_color(temp);  // calls insert_color(char color) function
 //verifies if the array is full or not and based on that decides in which state to jump
    current_state = (is_full()) ? WAIT_FULL : WAIT;
/*	if(is_full()){ current_state= WAIT_FULL;} 
    else { current_state= WAIT; }*/
}

void fn_WAIT_FULL(void) {
	wait_full(); //actions of wait_full state
}

void fn_ELIMINATE_COLOR(void){
	eliminate_color();   //calls function eliminate_color
	current_state= WAIT;  //changes the current_state to WAIT
}





/*
 * Title: gamelogic3.c
 * Primary Authors: Niccolò Cristoforetti
 * Helpers: -
 * Maintainability: Niccolò Cristoforetti
 * Date Creation: 29 set 2024
 */

#include "gamelogic3.h"
#include "game.h"

//Function that checks if the sequence is a tenctative or a correction. Returns a int for set the right index in the chronology
int16_t checkIfTenctOrCorrection(int8_t c){
    if( c=='X' || c== 'O' || c=='!' ){  //Check if the output isn't a correction
        return game.dim;
    }
    return 0;
}

//Function that inserts sequence or sequence corrections in chronology
void insertInChronology(int8_t* seq){
    j=checkIfTenctOrCorrection(seq[0]);  //The j index is used to insert correctly in the chronology the sequence or corrections
    for(i=0; i<game.dim; i++){
        game.chronology[ game.dim * 2 * game.count_tent - j + i ]=seq[i];  //The minus is used because when it's add the corrections the tenctative is already the next
    }
}

//Function that increases the number of tenctative
void incrementTent(void){
    game.count_tent++;
    printf("Number of current tentative: %d of %d \n",
           game.count_tent,
           game.tentatives);  //print number of count_tent/tentatives
}

//Function that checks if the maximum number of attempts has been reached
bool checkIfGameOver(void){
    if(game.count_tent<game.tentatives){
        return false;  //if the number of count_tent is less then tentatives the Game over condition isn't verified
    }
    return true;  //if the number of count_tent is equal (or more) than tentatives the Game over condition is verified
}

//Function that checks the difficulty degree
int8_t check_difficulty(void){
    return game.difficulty;
}

//Function that transforms the seq_user into corrections in EASY_MODE
void correctionsEasyMode(void){
    makeArrayEmpty_Bool(game.flags, 1, game.dim);  //Function for set all the flags to false
    for(i=0; i<game.dim; i++){
        if(tentative.seq_user[i]==game.seq_to_guess[i]){  //If the colour in the seq user corrispond to the colour of the sequence to guess in the same position
            tentative.seq_user[i]= 'X';  //That means the colour is correct and in the right position
            game.flags[i]=true;
        }
    }
    for (i=0; i<game.dim; i++) {
        for(j=0; j<game.dim; j++){
            if(tentative.seq_user[i]==game.seq_to_guess[j]){  //If the colour in the seq user corrispond to the colour of the sequence to guess in at least one position
                if(game.flags[j]!=true){  //If the colour in that position of the seq_to_guess was already been selected it must be ! not O
                    tentative.seq_user[i]= 'O';  //That means the colour is correct but in wrong position
                    game.flags[j]=true;
                    break;
                }
            }
        }
        if(tentative.seq_user[i]!='O' && tentative.seq_user[i]!='X'){  //If the colour doesn't exist in the sequence to guess (that means the output is neither 'O' and 'X')
            tentative.seq_user[i]= '!';  //The colour isn't correct
        }
    }
}
//Function that transforms the seq_user into corrections in MEDIUM_MODE
void correctionsMediumMode(void){
    int16_t o=0; int16_t x=0;
    correctionsEasyMode();
    for(i=0; i<game.dim; i++){
        switch (tentative.seq_user[i]) {
            case 'X': x++; break;
            case 'O': o++; break;
            case '!': break;
            default: exit(1);
        }  //This switch count the number of X O for reordinate the corrections for the medium mode
    }
    for(i=0; i<game.dim; i++){
        if(x>0){
            tentative.seq_user[i]='X';  //Firstly it's inserted the X based on the number the upper switch have finded
            x--;
        } else if (o>0){
            tentative.seq_user[i]='O';  //Secondly it's inserted the Y based on the number the upper switch have finded
            o--;
        } else {
            tentative.seq_user[i]='!';  //Lastly it's inserted the !
        }
    }
}

//Function that transforms the seq_user into corrections in DIFFICULT_MODE
void correctionsDifficultMode(void){
    correctionsMediumMode();
    for(i=0; i<game.dim; i++){
        if(tentative.seq_user[i]=='O'){
            tentative.seq_user[i]='!';  //Difficult mode showed only X and ! (not O)
        }
    }
}

//Function that prints the last sequence inserted in the chronology with the respective corrections
void printLastTentativeInChronology(void){
    printf("Sequence: ");
    for(i=0; i<game.dim; i++){
        printf("%c",
               game.chronology[game.dim*(game.count_tent-1)*2+i]);  //Print the last sequence inserted in the cronology
    }
    printf(" Corrections: ");
    for(i=0; i<game.dim; i++){
        printf("%c",
               game.chronology[game.dim*(game.count_tent-1)*2+game.dim+i]);  //Print the last corrections inserted in the cronology
    }printf("\n");
}

//Function that checks if the next state is WIN or not
bool winCondition(void){
    int i;
    for(i=0; i<game.dim; i++){
        if(game.chronology[game.dim*(game.count_tent-1)*2+i]!=game.seq_to_guess[i]){
            return false;  //If a value of the last sequence inserted in the chronology doesn't correspond to the sequence to guess the win condition is false
        }
    } return true;  //If all value of the last sequence inserted in the chronology correspond to the sequence to guess the win condition is true
}

//Function for ELABORATE_TENT state
void fn_ELABORATE_TENT(void){
    insertInChronology(tentative.seq_user);  //Insert sequence in chronology
    current_state = INCREMENT_TENT;  // Transition to the INCREMENT_TENT state;
}

//Function for INCREMENT_TENT state
void fn_INCREMENT_TENT(void){
    incrementTent();  //increment the number of count_tent
    if(checkIfGameOver()){
        current_state=GAME_OVER;  //if it's reached the number of tentatives the next state is GAME_OVER
    }else{
        switch (check_difficulty()) {  //otherwise a check_difficult must be made
            case 'A': current_state=EASY_MODE; break; // Transition to the EASY_MODE state
            case 'B': current_state=MEDIUM_MODE; break;  // Transition to the MEDIUM_MODE state
            case 'C': current_state=DIFFICULT_MODE; break;  // Transition to the DIFFICULT_MODE state
            default: exit(1);  //Error rises
        }
    }
}

//Function for GAME_OVER state
void fn_GAME_OVER(void){
    printf("you have reached the maximum number of attempts: GAME OVER!\n");  //Game over state
    current_state=ERROR;  //Transition to the ERROR state
}

//Function for EASY_MODE state
void fn_EASY_MODE(void){
    correctionsEasyMode();  //Set corrections for the easy mode in seq_user
    current_state=ELABORATE_RESULT;  //Transition to the ELABORATE_RESULT state
}

//Function for MEDIUM_MODE state
void fn_MEDIUM_MODE(void){
    correctionsMediumMode();  //Set corrections for the medium mode in seq_user
    current_state=ELABORATE_RESULT;  //Transition to the ELABORATE_RESULT state
}

//Function for DIFFICULT_MODE state
void fn_DIFFICULT_MODE(void){
    correctionsDifficultMode();  //Set corrections for the difficult mode in seq_user
    current_state=ELABORATE_RESULT;  //Transition to the ELABORATE_RESULT state
}

//Function for ELABORATE_RESULT state
void fn_ELABORATE_RESULT(void){
    insertInChronology(tentative.seq_user);  //Insert corrections in chronology
    printLastTentativeInChronology();  //Print the complete output of the last tentative
    displayResultsOnScreen();
    current_state = winCondition() ? WIN : RESET_TENT; // Transition to the next state based on the win condition
}

//Function for WIN state
void fn_WIN(void){
    printf("The sequence is correct: WIN in %d tenctatives!!!\n",
           game.count_tent);  //WIN state
    current_state=ERROR;  //Transition to the ERROR state
}

//#include "msp.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"
#define COLORS 6
#define DIFFICULTY 'A'
#define TENTATIVES 10
#define DIM 4
#define DOUBLES false

/* FUNCTION DECLARATIONS */
void fn_START(void);
void fn_KEY_WOUT_DOUB(void);
void fn_KEY_WH_DOUB(void);
void fn_S_TENT(void);
/*ENUM DECLARATION*/
typedef enum {START, KEY_WOUT_DOUB, KEY_WH_DOUB, S_TENT, ERROR} State;
typedef struct {
    State state;
    void (*state_function)(void);
} StateMachine;
/* FINITE STATE MACHINE IMPLEMENTATION */
StateMachine fsm[]={
    {START, fn_START},
    {KEY_WOUT_DOUB, fn_KEY_WOUT_DOUB},
    {KEY_WH_DOUB, fn_KEY_WH_DOUB},
    {S_TENT, fn_S_TENT}
};
State current_state=START;
/* Struct of the Program */
typedef struct {
    int dim;
    char difficulty;
    bool doubles;
    int count_tent;
    int tentatives;
    char* seq_to_guess;
    char* chronology;
} Game;
typedef struct {
    int count;
    int dim;
    int* seq_user;
} Tentative;
Game game;
Tentative tentative;
/* Function to clean an array */
void makeArrayEmpty_Char(char* array, int par1, int par2) {
    for (int i=0; i<par1; i++) {
        for (int j=0; j<par2; j++) {
            array[i*par1+j]=0;
        }
    }
}
void makeArrayEmpty_Int(int* array, int par1, int par2) {
    for (int i=0; i<par1; i++) {
        for (int j=0; j<par2; j++) {
            array[i*par1+j]=0;
        }
    }
}
/* Initialize Game struct with parameters passed*/
void allocate_in_Heap_Char(char** array, int par1, int par2) {
    *array=(char*)malloc(par1*par2*sizeof(char));
    if(*array==NULL) {
        printf("Error! memory not allocated.");
        exit(1);
    }
    makeArrayEmpty_Char(*array, par1, par2);
}
void allocate_in_Heap_Int(int** array, int par1, int par2) {
    *array=(int*)malloc(par1*par2*sizeof(int));
    if(*array==NULL) {
        printf("Error! memory not allocated.");
        exit(1);
    }
    makeArrayEmpty_Int(*array, par1, par2);
}
void initGame(int dim, char diff, bool doubles, int tents) {
    game.dim=dim;
    game.difficulty=diff;
    game.doubles=doubles;
    game.count_tent=0;
    game.tentatives=tents;
    allocate_in_Heap_Char(&game.seq_to_guess, 1, game.dim);
    allocate_in_Heap_Char(&game.chronology, game.tentatives, game.dim*2);
}
void deallocate_Char(char* array) {
    free(array);
    array=NULL;
}
void deallocate_Int(int* array) {
    free(array);
    array=NULL;
}
/* Key generation with doubles */
int random_int (int min, int max) {
    return rand()%(max-min+1)+min;
}
int* key_generation_wh_doub(void) {
    int* array=NULL;
    allocate_in_Heap_Int(&array, 1, game.dim);
    for (int i=0; i<game.dim; i++) {
        array[i]=random_int(1, COLORS);
    }
    return array;
}
bool presence_Double (int* array, int value, int dim) {
    if (dim==1) {
        return false;
    }
    for (int i=0; i<dim-1; i++) {
        if (array[i]==value) {
            return true;
        }
    }
    return false;
}
int* key_generation_wout_doub(void) {
    int* array=NULL;
    allocate_in_Heap_Int(&array, 1, game.dim);
    for (int i=0; i<game.dim; i++) {
        int value=random_int(1, COLORS);
        if(!(presence_Double(array, value, i+1))) {
            array[i]=value;
        }
        else {
            i--;
        }
    }
    return array;
}
char int_Conversion_to_Char (int index) {
    char c='\0';
    switch (index) {
        case 1: c='R'; break;
        case 2: c='G'; break;
        case 3: c='B'; break;
        case 4: c='Y'; break;
        case 5: c='P'; break;
        case 6: c='C'; break;
        default: {
            fprintf(stderr, "Unrecoverable Error");
            exit(1);
        }
    }
    return c;
}
void crypt_sequence_Int_Char(int* arr1, char* arr2, int dim) {
    for (int i=0; i<dim; i++) {
        arr2[i]=int_Conversion_to_Char(arr1[i]);
    }
}
void continue_Key_Decryption(int* sequence) {
    for (int i=0; i<game.dim; i++) {
        printf("%d", sequence[i]);
    }
    printf("\n");
    crypt_sequence_Int_Char(sequence, game.seq_to_guess, game.dim);
    for (int i=0; i<game.dim; i++) {
        printf("%c", game.seq_to_guess[i]);
    }
    printf("\n");
    deallocate_Int(sequence);

}
/*Initializes the components*/
void fn_START(void) {
    initGame(DIM, DIFFICULTY, DOUBLES, TENTATIVES);
    /* Jump to next phase */
    if(game.doubles) {
        current_state=KEY_WH_DOUB;
    }
    else {
        current_state=KEY_WOUT_DOUB;
    }
}
void fn_KEY_WOUT_DOUB(void) {
    int* sequence=key_generation_wout_doub();
    continue_Key_Decryption(sequence);
    current_state=S_TENT;
}
void fn_KEY_WH_DOUB(void) {
    int* sequence=key_generation_wh_doub();
    continue_Key_Decryption(sequence);
    current_state=S_TENT;
}
void fn_S_TENT(void) {
    
}
/**
 * main.c
 */
int main(void)
{
    srand((unsigned)time(NULL));
    //WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    while (1) {
        if (current_state < ERROR) {
            (*fsm[current_state].state_function)();
        }
        else {
            /* ERROR */
        }
        /* TO BE REMOVED */
        if (current_state==ERROR-1) {
            deallocate_Char(game.seq_to_guess);
            deallocate_Char(game.chronology);
            break;
        }
    }
    return 0;
}

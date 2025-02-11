//
//  game.c
//  Mastermind Program
//
//  Created by Matteo Gottardelli on 27/09/24.
//
#include "gamelogic1.h"
int i, j;
/* Deallocate memory for a character array */
void deallocate_Char(char* array) {
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}

/* Deallocate memory for an integer array */
void deallocate_Int(int* array) {
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/* Deallocates boolean array memory */
void deallocate_Bool(bool* array){
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/* Function to clean a character array */
void makeArrayEmpty_Char(char* array, int par1, int par2) {
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to zero
        }
    }
}
/* Function to clean an integer array */
void makeArrayEmpty_Int(int* array, int par1, int par2) {
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to zero
        }
    }
}
/* Initializes a boolean array to false */
void makeArrayEmpty_Bool(bool* array, int par1, int par2){
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to false
        }
    }
}

/* Memory allocation for a character array */
void allocate_in_Heap_Char(char** array, int par1, int par2) {
    if (array!=NULL) {
        deallocate_Char(*array);
    }
    *array = (char*)malloc(par1 * par2 * sizeof(char));
    if (*array == NULL) {
        printf("Error! memory not allocated."); // Handle memory allocation failure
        exit(1);
    }
    makeArrayEmpty_Char(*array, par1, par2); // Initialize the allocated array
}

/* Memory allocation for an integer array */
void allocate_in_Heap_Int(int** array, int par1, int par2) {
    if (array!=NULL) {
        deallocate_Int(*array);
    }
    *array = (int*)malloc(par1 * par2 * sizeof(int));
    if (*array == NULL) {
        printf("Error! memory not allocated."); // Handle memory allocation failure
        exit(1);
    }
    makeArrayEmpty_Int(*array, par1, par2); // Initialize the allocated array
}

/*Memory allocation for a boolean array*/
void allocate_in_Heap_Bool(bool** array, int par1, int par2){
    if (array!=NULL) {
        deallocate_Bool(*array);
    }
    *array = (bool*)malloc(par1 * par2 * sizeof(bool));
    if (*array == NULL) {
        printf("Error! memory not allocated."); // Handle memory allocation failure
        exit(1);
    }
    makeArrayEmpty_Bool(*array, par1, par2); // Initialize the allocated array
}

/* Initialize the game with parameters */
void initGame(int dim, char diff, bool doubles, int tents) {
    game.dim = dim;                     // Set the dimension
    game.difficulty = diff;             // Set the difficulty
    game.doubles = doubles;              // Set the doubles flag
    game.count_tent = 0;                // Initialize current attempt count
    game.tentatives = tents;             // Set the total number of attempts
    allocate_in_Heap_Char(&game.seq_to_guess, 1, game.dim); // Allocate memory for the sequence to guess
    allocate_in_Heap_Char(&game.chronology, game.tentatives, game.dim * 2); // Allocate memory for attempt history
    allocate_in_Heap_Bool(&game.flagsGuess, 1, game.dim);  //allocate memory for flags
    allocate_in_Heap_Bool(&game.flagsUsr, 1, game.dim);  //allocate memory for flags
}

/* Generate a random integer between min and max */
int random_int(int min, int max) {
    return rand() % (max - min + 1) + min; // Return a random integer within the specified range
}

/* Generate a key with doubles allowed */
int* key_generation_wh_doub(void) {
    int* array = NULL;
    allocate_in_Heap_Int(&array, 1, game.dim); // Allocate memory for the key
    for (i = 0; i < game.dim; i++) {
        array[i] = random_int(1, COLORS); // Assign random values to the array
    }
    return array; // Return the generated key
}

/* Check if a value is already present in the array */
bool presence_Double(int* array, int value, int dim) {
    if (dim == 1) return false; // If array has only one element, no duplicates possible
    for (i = 0; i < dim - 1; i++) {
        if (array[i] == value) return true; // Return true if the value is found
    }
    return false; // Return false if the value is not found
}

/* Generate a key without allowing doubles */
int* key_generation_wout_doub(void) {
    int* array = NULL;
    allocate_in_Heap_Int(&array, 1, game.dim); // Allocate memory for the key
    for (i = 0; i < game.dim; i++) {
        int value = random_int(1, COLORS); // Generate a random value
        if (!presence_Double(array, value, i + 1)) {
            array[i] = value; // Assign value if not already present
        } else {
            i--; // Decrement index to retry
        }
    }
    return array; // Return the generated key
}

/* Convert an integer index to a character */
char int_Conversion_to_Char(int index) {
    char c = '\0';
    switch (index) {
        case 1: c = 'R'; break; // Red
        case 2: c = 'G'; break; // Green
        case 3: c = 'B'; break; // Blue
        case 4: c = 'Y'; break; // Yellow
        case 5: c = 'P'; break; // Purple
        case 6: c = 'C'; break; // Cyan
        default: exit(1); // Exit on error
    }
    return c; // Return the character representation
}

/* Convert an integer array to a character array */
void crypt_sequence_Int_Char(int* arr1, char* arr2, int dim) {
    for (i = 0; i < dim; i++) {
        arr2[i] = int_Conversion_to_Char(arr1[i]); // Convert each integer to character
    }
}

/* Continue the key decryption process */
void continue_Key_Decryption(int* sequence) {
    for (i=0; i<game.dim; i++) {
        printf("%d", sequence[i]);
    }
    printf("\n");
    crypt_sequence_Int_Char(sequence, game.seq_to_guess, game.dim); // Convert the sequence
    for (i=0; i<game.dim; i++) {
        printf("%c", game.seq_to_guess[i]);
    }
    printf("\n");
    deallocate_Int(sequence); // Free the sequence memory
}

/* Reset the user's tentative state */
void resetTentative(void) {
    tentative.count = 0; // Reset attempt count
    tentative.dim = game.dim; // Set dimension for user's sequence
    allocate_in_Heap_Char(&tentative.seq_user, 1, game.dim); // Allocate memory for user's guesses
}

/* Function for the START state */
void fn_START(void) {
    initGame(DIM, DIFFICULTY, DOUBLES, TENTATIVES); // Initialize the game
    current_state = game.doubles ? KEY_WH_DOUB : KEY_WOUT_DOUB; // Transition to the next state based on doubles flag
}

/* Function for the KEY_WOUT_DOUB state */
void fn_KEY_WOUT_DOUB(void) {
    int* sequence = key_generation_wout_doub(); // Generate key without doubles
    continue_Key_Decryption(sequence); // Continue the decryption process
    current_state = RESET_TENT; // Transition to the next state
}

/* Function for the KEY_WH_DOUB state */
void fn_KEY_WH_DOUB(void) {
    int* sequence = key_generation_wh_doub(); // Generate key with doubles
    continue_Key_Decryption(sequence); // Continue the decryption process
    current_state = RESET_TENT; // Transition to the next state
}

/* Function for the RESET_TENT state */
void fn_RESET_TENT(void) {
    resetTentative(); // Reset user's tentative state
    current_state = WAIT; // Transition to the ERROR state
}


/*
 * Title: gamelogic1.c
 * Primary Authors: Matteo Gottardelli
 * Helpers: -
 * Maintainability: Matteo Gottardelli
 * Date Creation: 27 set 2024
 */
#include "gamelogic1.h"
#include "implementations.h"
#include "game.h"
#include "chronology.h"
int i, j;
void emergency() {
    deallocate_Char(game.seq_to_guess); // Deallocate sequence memory
    deallocate_Char(game.chronology); // Deallocate chronology memory
    deallocate_Bool(game.flags); //Deallocate flag memory
    for (i = 0; i < sizes[CHRONOLOGY]; i++) {
        if (chronology[i].button.state != DISABLED) {
            free(chronology[i].num.string);  // Free each dynamically allocated string
            for(j=0; j<game.dim; j++){
            free(chronology[i].chrono_buttons[j].text.string);
            }
        }
    }
}
/* Deallocate memory for a character array */
void deallocate_Char(int8_t* array) {
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}

/* Deallocate memory for an integer array */
void deallocate_Int(int16_t* array) {
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/* Deallocates boolean array memory */
void deallocate_Bool(bool* array){
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/* Function to clean a character array */
void makeArrayEmpty_Char(int8_t* array, int16_t par1, int16_t par2) {
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to zero
        }
    }
}
/* Function to clean an integer array */
void makeArrayEmpty_Int(int16_t* array, int16_t par1, int16_t par2) {
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to zero
        }
    }
}
/* Initializes a boolean array to false */
void makeArrayEmpty_Bool(bool* array, int16_t par1, int16_t par2){
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to false
        }
    }
}

/* Memory allocation for a character array */
void allocate_in_Heap_Char(int8_t** array, int16_t par1, int16_t par2) {
    if (*array!=NULL) {
        deallocate_Char(*array);
    }
    if(par1!=0 && par2!=0) {
            *array =malloc(par1 * par2 * sizeof(int8_t));
            if (*array == NULL) {
                emergency();
                printf("Error! memory not allocated."); // Handle memory allocation failure
                exit(1);
            }
            makeArrayEmpty_Char(*array, par1, par2); // Initialize the allocated array
        }
}

/* Memory allocation for an integer array */
void allocate_in_Heap_Int(int16_t** array, int16_t par1, int16_t par2) {
    if (*array!=NULL) {
        deallocate_Int(*array);
    }
    if(par1!=0 && par2!=0) {
            *array =malloc(par1 * par2 * sizeof(int16_t));
            if (*array == NULL) {
                emergency();
                printf("Error! memory not allocated."); // Handle memory allocation failure
                exit(1);
            }
            makeArrayEmpty_Int(*array, par1, par2); // Initialize the allocated array
        }
}

/*Memory allocation for a boolean array*/
void allocate_in_Heap_Bool(bool** array, int16_t par1, int16_t par2){
    if (array!=NULL) {
        deallocate_Bool(*array);
    }
    if(par1!=0 && par2!=0) {
        *array =malloc(par1 * par2 * sizeof(bool));
        if (*array == NULL) {
            emergency();
            printf("Error! memory not allocated."); // Handle memory allocation failure
            exit(1);
        }
        makeArrayEmpty_Bool(*array, par1, par2); // Initialize the allocated array
    }
}

/* Initialize the game with parameters */
void initGame(int16_t dim, int8_t diff, bool doubles, int16_t tents) {
    game.dim = dim;                     // Set the dimension
    game.difficulty = diff;             // Set the difficulty
    game.doubles = doubles;              // Set the doubles flag
    game.count_tent = 0;                // Initialize current attempt count
    game.tentatives = tents;             // Set the total number of attempts
    allocate_in_Heap_Char(&game.seq_to_guess, 1, game.dim); // Allocate memory for the sequence to guess
    allocate_in_Heap_Char(&game.chronology, game.tentatives, game.dim * 2); // Allocate memory for attempt history
    allocate_in_Heap_Bool(&game.flags, 1, game.dim);  //allocate memory for flags
}

/* Generate a random integer between min and max */
int random_int(int16_t min, int16_t max) {
    return rand() % (max - min + 1) + min; // Return a random integer within the specified range
}

/* Generate a key with doubles allowed */
int16_t* key_generation_wh_doub(void) {
    int16_t* array = NULL;
    allocate_in_Heap_Int(&array, 1, game.dim); // Allocate memory for the key
    for (i = 0; i < game.dim; i++) {
        array[i] = random_int(1, COLORS); // Assign random values to the array
    }
    return array; // Return the generated key
}

/* Check if a value is already present in the array */
bool presence_Double(int16_t* array, int16_t value, int16_t dim) {
    if (dim == 1) return false; // If array has only one element, no duplicates possible
    for (i = 0; i < dim - 1; i++) {
        if (array[i] == value) return true; // Return true if the value is found
    }
    return false; // Return false if the value is not found
}

/* Generate a key without allowing doubles */
int16_t* key_generation_wout_doub(void) {
    int16_t* array = NULL;
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
int8_t int_Conversion_to_Char(int16_t index) {
    char c = '\0';
    switch (index) {
        case 1: c = 'R'; break; // Red
        case 2: c = 'G'; break; // Green
        case 3: c = 'B'; break; // Blue
        case 4: c = 'Y'; break; // Yellow
        case 5: c = 'P'; break; // Purple
        case 6: c = 'C'; break; // Cyan
        case 7: c = 'O'; break; // Orange
        case 8: c = 'W'; break; //White
        default: exit(1); // Exit on error
    }
    return c; // Return the character representation
}

/* Convert an integer array to a character array */
void crypt_sequence_Int_Char(int16_t* arr1, int8_t* arr2, int16_t dim) {
    for (i = 0; i < dim; i++) {
        arr2[i] = int_Conversion_to_Char(arr1[i]); // Convert each integer to character
    }
}

/* Continue the key decryption process */
void continue_Key_Decryption(int16_t* sequence) {
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
    pos_chronology = 0;
    tentative.dim = game.dim; // Set dimension for user's sequence
    position=0;
    allocate_in_Heap_Char(&tentative.seq_user, 1, game.dim); // Allocate memory for user's guesses
    for (i=0; i<game.dim; i++) {
        circles[i].color=STANDARD_COLOR;
    }
    pos_chronology=0;
    fn_GAME();
}

/* Function for the START state */
//ABILITATE initGame HERE and disable in fn_GAME
void fn_START(void) {
    //initGame(game.dim, game.difficulty, game.doubles, game.tentatives); // Initialize the game
    //initGame(3, 'A', true, 7); // Initialize the game
    current_state = game.doubles ? KEY_WH_DOUB : KEY_WOUT_DOUB; // Transition to the next state based on doubles flag
}

/* Function for the KEY_WOUT_DOUB state */
void fn_KEY_WOUT_DOUB(void) {
    int16_t* sequence = key_generation_wout_doub(); // Generate key without doubles
    continue_Key_Decryption(sequence); // Continue the decryption process
    current_state = RESET_TENT; // Transition to the next state
}

/* Function for the KEY_WH_DOUB state */
void fn_KEY_WH_DOUB(void) {
    int16_t* sequence = key_generation_wh_doub(); // Generate key with doubles
    continue_Key_Decryption(sequence); // Continue the decryption process
    current_state = RESET_TENT; // Transition to the next state
}

/* Function for the RESET_TENT state */
void fn_RESET_TENT(void) {
    resetTentative(); // Reset user's tentative state
    current_state = WAIT; // Transition to the ERROR state
}


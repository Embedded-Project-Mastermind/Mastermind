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
/**
 * @brief Function that deallocated dynamic allocated memory and is called if there are unexpected behaviors in the code
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void emergency() {
    deallocate_Char(game.seq_to_guess); // Deallocate sequence memory
    deallocate_Char(game.chronology); // Deallocate chronology memory
    deallocate_Bool(game.flags); //Deallocate flag memory
    deallocate_Char(tentative.seq_user);
    deallocate_Char(tentative.sol_user);
    for (i = 0; i < sizes[CHRONOLOGY]; i++) {
        if (chronology[i].button.state != DISABLED) {
            free(chronology[i].num.string);  // Free each dynamically allocated string
            for(j=0; j<game.dim; j++){
                free(chronology[i].chrono_buttons[j].text.string);
            }
        }
    }
}
/**
 * @brief Deallocate memory for a character array setting then that allocation to null for being sure
 * @param array Char array reference for a deallocation
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void deallocate_Char(int8_t* array) {
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/**
 * @brief Deallocate memory for an integer array setting then that allocation to null for being sure
 * @param array Integer array reference for a deallocation
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void deallocate_Int(int16_t* array) {
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/**
 * @brief Deallocate memory for a boolean array setting then that allocation to null for being sure
 * @param array Boolean array reference for a deallocation
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void deallocate_Bool(bool* array){
    free(array);    // Free allocated memory
    array = NULL;   // Set pointer to NULL
}
/**
 * @brief Initialization for a character array setting to its default state
 * @param array Char array reference for a deallocation
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void makeArrayEmpty_Char(int8_t* array, int16_t par1, int16_t par2) {
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to zero
        }
    }
}
/**
 * @brief Initialization for an integer array setting to its default state
 * @param array Integer array reference for a deallocation
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void makeArrayEmpty_Int(int16_t* array, int16_t par1, int16_t par2) {
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to zero
        }
    }
}

/**
 * @brief Initialization for a boolean array setting to its default state
 * @param array Boolean array reference for a deallocation
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void makeArrayEmpty_Bool(bool* array, int16_t par1, int16_t par2){
    for (i = 0; i < par1; i++) {
        for (j = 0; j < par2; j++) {
            array[i * par1 + j] = 0; // Set each element to false
        }
    }
}
/**
 * @brief Allocation for a character array, ensuring that it is not already allocated
 * @param array Double Char Reference for allocation Matrix
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
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
/**
 * @brief Allocation for an integer array, ensuring that it is not already allocated
 * @param array Double Integer Reference for allocation Matrix
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
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
/**
 * @brief Allocation for a boolean array, ensuring that it is not already allocated
 * @param array Double Boolean Reference for allocation Matrix
 * @param par1 First dimension of the matrix
 * @param par2 Second dimension of the matrix
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
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

/**
 * @brief Initialize the game with parameters selected from the GUI interface from DIMENSION, DIFFICULTY, TENTATIVES, DOUBLES
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void initGame(int16_t dim, int8_t diff, bool doubles, int16_t tents) {
    game.dim = dim;                     // Set the dimension
    game.difficulty = diff;             // Set the difficulty
    game.doubles = doubles;              // Set the doubles flag
    game.count_tent = 0;                // Initialize current attempt count
    game.tentatives = tents;             // Set the total number of attempts
    allocate_in_Heap_Char(&game.seq_to_guess, 1, game.dim); // Allocate memory for the sequence to guess
    if(game.tentatives!=0) {
        allocate_in_Heap_Char(&game.chronology, game.tentatives, game.dim * 2); // Allocate memory for attempt history
    }
    else {
        allocate_in_Heap_Char(&game.chronology, 7, game.dim * 2);
    }
    allocate_in_Heap_Bool(&game.flags, 1, game.dim);  //allocate memory for flags
}
/**
 * @brief Generation of a random integer with two limits
 * @param min Minimum value of the interval
 * @param max Maximum value of the interval
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
int random_int(int16_t min, int16_t max) {
    return rand() % (max - min + 1) + min; // Return a random integer within the specified range
}
/**
 * @brief Generation of a random key that allows the presence of duplicates colors
 * @return returns the array generated to a reference
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
int16_t* key_generation_wh_doub(void) {
    int16_t* array = NULL;
    allocate_in_Heap_Int(&array, 1, game.dim); // Allocate memory for the key
    for (i = 0; i < game.dim; i++) {
        array[i] = random_int(1, COLORS); // Assign random values to the array
    }
    return array; // Return the generated key
}
/**
 * @brief Check if the array has already a value that I would like to insert in it
 * @param array Current array from which we would want to verify the presence
 * @param value Corresponds to the value we would like to verify the presence of
 * @param dim Total length of the array, we are currently passing
 * @return bool - returns the result of this if - TRUE it is already present, FALSE that color is not present in the sequence
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
bool presence_Double(int16_t* array, int16_t value, int16_t dim) {
    if (dim == 1) return false; // If array has only one element, no duplicates possible
    for (i = 0; i < dim - 1; i++) {
        if (array[i] == value) return true; // Return true if the value is found
    }
    return false; // Return false if the value is not found
}
/**
 * @brief Generation of a random key that doesn't allow the presence of duplicates colors
 * @return returns the array generated to a reference
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
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
/**
 * @brief Convertion of a element from the integer format to the char format
 * @param index Integer format value
 * @return int8t returned char format value
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
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
/**
 * @brief Convertion of an array from the integer format to the char format
 * @param arr1 Integer format array
 * @param arr2 Char format array
 * @param dim Total dimension of the array
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void crypt_sequence_Int_Char(int16_t* arr1, int8_t* arr2, int16_t dim) {
    for (i = 0; i < dim; i++) {
        arr2[i] = int_Conversion_to_Char(arr1[i]); // Convert each integer to character
    }
}
/**
 * @brief Analysis and parsing of the integer sequence to the char one, with an appropriate deallocation of the integer one
 * @param sequence Parsed sequence in integer format
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
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
/**
 * @brief After each input sequence is analyzed the tentative is all reinitialized with an incrementation of the tentative count
 * @return void
 * @author Matteo Gottardelli (Primary Author & Maintainer)
 * @date 2024-09-27
 */
void resetTentative(void) {
    deallocate_Char(tentative.seq_user);
    deallocate_Char(tentative.sol_user);
    tentative.count = 0; // Reset attempt count
    pos_chronology = 0;  // Reset chronology position count
    tentative.dim = game.dim; // Set dimension for user's sequence
    position=0;
    allocate_in_Heap_Char(&tentative.seq_user, 1, game.dim); // Allocate memory for user's guesses
    allocate_in_Heap_Char(&tentative.sol_user, 1, game.dim);
    for (i=0; i<game.dim; i++) {
        circles[i].color=STANDARD_COLOR;
    }
    pos_chronology=0;
    fn_GAME();
}

/* Function for the START state */
//ABILITATE initGame HERE and disable in fn_GAME
void fn_START(void) {
    initGame(game.dim, game.difficulty, game.doubles, game.tentatives); // Initialize the game
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

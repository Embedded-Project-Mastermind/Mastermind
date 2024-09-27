#include "msp.h"
#include "boolean.h"
#define COLORS 6
#define TENTATIVES 10
#define DIM 4
#define DOUBLES false;

typedef enum {START} State;
typedef struct {
	State state;
	void (*state_function)(void);
} StateMachine;
typedef struct {
	int dim;
	char difficulty;
	bool doubles;
	int tentatives;
	char* seq_to_guess;
} Game;
typedef struct {
	int count;
	int dim;
	int* seq_user;
} Tentative;

Game game;
Tentative tentative;
char* chronology;
/* FUNCTION DECLARATIONS */
void fn_INIT();
/* FINITE STATE MACHINE IMPLEMENTATION */
StateMachine fms[]={
	{INIT, fn_INIT} 
};

State current_state=INIT;

void fn_INIT() {

}
/**
 * main.c
 */
void main(void)
{
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;		// stop watchdog timer
}

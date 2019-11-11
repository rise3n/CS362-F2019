#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

void assert(int condition) {
	if (condition)
		printf("assertion pass\n");
	else
		printf("assertion not pass\n");

}

int refactored_mine(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos) {
	int i, hnum = 0, result = 0, pre = 0, post = 0,predis=0;
	state->coins = getCost(mine);
	pre = state->handCount[currentPlayer];
	predis = state->discardCount[currentPlayer];
	result = play_mine(choice1, choice2, currentPlayer, state, handPos);
	post = state->handCount[currentPlayer];

	assert(state->discardCount[currentPlayer] == (predis+1) );//see if only mine is discarded here. If not pass, then the bug 1 is exposed.
	assert(post == (pre-1) );// check if the number of cards makes sense here. If not pass, then the bug 2 is exposed
	endTurn(state);
}

int main() {
	// set your card array
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall };
	// declarethe game state
	struct gameState G;// declare the arrays 
	int coppers[MAX_HAND];
	int silvers[MAX_HAND];
	int golds[MAX_HAND];
	int bonus = 0, r, i;

	printf("Begin TestingsomeFunction():\n");//// set the state of your variables// comment on what this is going totest//
	memset(&G, 32, sizeof(struct gameState));   // set the game state
	printf("line\n");
	r = initializeGame(2, k, 10, &G); // initialize a new game
	printf("line\n");
	for (i = 0; i < G.handCount[0]; i++) {
		G.hand[0][i] = copper;
	}// set all position to -1 for following test
	G.hand[0][0] = mine;
	printf("line\n");
	refactored_mine(1,5,0, &G, 0);//position 0 is mine, 1 is copper.
	printf("line\n");
	printf("unit test 5 finish");

}
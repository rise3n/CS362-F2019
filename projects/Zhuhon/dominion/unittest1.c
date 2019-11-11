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

int refactored_baron(int choice1, int currentPlayer, struct gameState *state, int handPos, int* bonus) {
	int i, hnum = 0, result = 0;
	state->coins = getCost(baron);
	result = play_baron( choice1, currentPlayer, state, handPos,bonus);
	for (i = 0; i < MAX_HAND; i++) {
			if(state->hand[currentPlayer][i]!=-1)
			hnum += 1;

	}

	assert(hnum==state->handCount[currentPlayer]);//see if handcount matches the actual number of cards. check bug1. if not match then the bug is exposed.
	assert(state->discardCount[currentPlayer] == 2);// see if the card is correctly discarded. check bug2. should be 2 here because discard baron and estate. if the assertion fail, then the bug is exposed.
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
	int r,i,bonus=0;

	printf("Begin TestingsomeFunction():\n");//// set the state of your variables// comment on what this is going totest//
	memset(&G, 32, sizeof(struct gameState));   // set the game state
	printf("line\n");
	r = initializeGame(2, k, 10, &G); // initialize a new game
	printf("line\n");

	for (i = 10; i < MAX_HAND; i++) {
		G.hand[0][i]=-1;
	}// set unused position to -1.
	printf("line\n");
	gainCard(1, &G, 2, 0);
	gainCard(15,&G,2,0); //gain two card
	printf("line\n");
	refactored_baron(1, 0,&G, G.hand[0][G.handCount[0]-1],&bonus);
	printf("line\n");
	gainCard(15, &G, 2, 0);//get an baron again
	int hnum = 0, result = 0;
	hnum = fullDeckCount(0, estate, &G);
	result = play_baron(0, 0, &G, G.hand[0][G.handCount[0] - 1], bonus);

	assert(fullDeckCount(0,estate,&G)>hnum);//see if more estate if dont
	

	printf("unit test 1 finish");

}
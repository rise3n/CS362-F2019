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

int refactored_tribute(int currentPlayer, struct gameState *state, int handPos, int* bonus) {
	int i, hnum = 0, result = 0, pre = 0, post = 0;
	int tributeRevealedCards[2] = { -1, -1 };
	state->coins = getCost(tribute);
	pre = state->discardCount[1];
	result = tributeEffect(currentPlayer, state);//currentPlayer is 0 and nextPlayer is 1.
	post = state->discardCount[1];

	assert( post==(pre+3) );//see if player get correct bonus. If not, then the bug 2 is exposed.
	//assert(tributeRevealedCards[1]>0 && tributeRevealedCards[1]<27);// check if revealed cards are valid. If not, bug 1 is exposed.
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
	for (i = 0; i < G.deckCount[1]; i++) {
		G.deck[1][i] = copper;
	}// set all position to -1 for following test

	printf("line\n");
	refactored_tribute(0, &G, 2, &bonus);
	printf("line\n");

	G.deck[1][0] = copper;
	G.deckCount[1] = 1;

	int hnum = 0, result = 0, pre = 0, post = 0;
	int tributeRevealedCards[2] = { -1, -1 };
	
	pre = G.discardCount[1];
	tributeEffect(0, &G);//currentPlayer is 0 and nextPlayer is 1.
	post = G.discardCount[1];
	assert(post==(pre+2) );

	G.deckCount[1] = 0;
	G.discardCount[1] = 1;
	G.discard[1][0] = copper;

	tributeEffect(0,&G);

	assert(G.coins == 2);
	G.deckCount[1] = 0;
	G.discardCount[1] = 0;

	tributeEffect(0, &G);
	//assert(result == -1);

	printf("unit test 4 finish");

}
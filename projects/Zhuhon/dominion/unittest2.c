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

int refactored_minion(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos, int *bonus) {
	int i, hnum = 0, result = 0;
	state->coins = getCost(minion);
	result = play_minion(choice1,choice2, currentPlayer, state, handPos, bonus);

	for (i = 0; i < MAX_HAND; i++) {
		if (state->hand[currentPlayer][i] != -1)
			hnum += 1;

	}

	assert(state->numActions==2);//see if action is added. it is 2 here because numAction-- is in playcard(), just call play_minion()should increase numAction by 1, which should be 2
	//if not pass then the bug 1 is exposed.
	assert(hnum==4);// see if player do get 4 cards, if not pass then the bug 2 is exposed
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
	for (i = 10; i < MAX_HAND; i++) {
		G.hand[0][i] = -1;
	}// set unused position to -1.
	printf("line\n");
	gainCard(17, &G, 2, 0); //gain two card
	printf("line\n");
	refactored_minion(0,1, 0, &G, G.hand[0][G.handCount[0] - 1], &bonus);
	printf("line\n");
	//int hnum = 0, result = 0;
	//result = play_minion(1, 0, 0, &G, G.hand[0][G.handCount[0] - 1], &bonus);
	//assert(G.coins == 2);
	//G.hand[1][0] = copper;
	//G.hand[1][1] = copper;
	//G.hand[1][2] = copper;
	//G.hand[1][2] = copper;
	//G.hand[1][2] = copper;
	//G.handCount[1] = 5;

	//result = play_minion(0, 1, 0, &G, G.hand[0][G.handCount[0] - 1], &bonus);
	//assert(G.handCount[1] == 4);

	printf("unit test 2 finish\n");

}
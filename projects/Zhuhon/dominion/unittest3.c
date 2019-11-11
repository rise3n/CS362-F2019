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

int refactored_ambassador(int choice1, int choice2, int currentPlayer, struct gameState *state, int handPos) {
	int i, hnum = 0, result = 0, pre = 0, post = 0;
	state->coins = getCost(ambassador);

	pre = state->supplyCount[state->hand[currentPlayer][choice1]];
	result = play_ambassador(choice1, choice2, currentPlayer, state, handPos);
	post = state->supplyCount[state->hand[currentPlayer][choice1]];

	assert(result == -1);//see if player have enough card to discard, it should be -1 here becasue reveal an estate and there are one estate left in player's hand. If not pass then bug 1 is exposed.
	assert(post==pre);// check if supply has more cards, should be 1 more(2 copies and just 1 other player). If not pass then the bug 2 is exposed.
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
	int bonus = 0, r, i,result=0;

	printf("Begin TestingsomeFunction():\n");//// set the state of your variables// comment on what this is going totest//
	memset(&G, 32, sizeof(struct gameState));   // set the game state
	printf("line\n");
	r = initializeGame(2, k, 10, &G); // initialize a new game
	printf("line\n");
	for (i = 0; i < MAX_HAND; i++) {
		G.hand[0][i] = -1;
	}// set all position to -1 for following test
	G.hand[0][0] = estate;
	G.hand[0][1] = estate;
	G.hand[0][2] = ambassador;

	printf("line\n");
	refactored_ambassador(0, 2, 0, &G, 2);
	printf("line\n");
	G.hand[0][2] = estate;
	G.hand[0][3] = ambassador;
	int pre = fullDeckCount(0, 1, &G);
	result=playCard(3,0, 2, 0, &G);
	assert(result != -1);
	assert(fullDeckCount(0,1 ,&G)<pre);//should be smaller
	isGameOver(&G);

	printf("unit test 3 finish\n");

}
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
//#include <assert.h>
#include "rngs.h"
#include<stdlib.h>
#include<time.h>

int main() {
	struct gameState Game;
	int kingdom[10] = { adventurer, council_room, tribute, minion, mine, remodel, smithy, village, baron, great_hall };
	int i, j, k, num_of_player, errors = 0, fails = 0, pass = 0, result, choice1, choice2;//fails is the number of failues due to random numbers.
	int deck[4] = { -1,-1,-1,-1 };//deck and hand save the randomized results of deck and hand count.
	int hand[4] = { -1,-1,-1,-1 };
	int preCoin[4] = { -1,-1,-1,-1 };
	int tributeRevealedCards[2] = { -1, -1 };
	int discard[4] = { 0,0,0,0 };
	int bonus=0;

	printf("start random test for tribute\n");
	//execute random test for 1000 times

	srand(time(NULL));

	for (i = 0; i < 1000; i++) {
		num_of_player = rand() % 3 + 2;
		memset(&Game, 0, sizeof(struct gameState));
		initializeGame(num_of_player, kingdom, 10, &Game);

		for (j = 0; j < num_of_player; j++) {
			//randomize deck
			Game.deckCount[j] = rand() % 20 + 4;//4-23
			deck[j] = Game.deckCount[j];
			for (k = 0; k < (deck[j] / 2); k++) {
				Game.deck[j][k] = kingdom[(rand() % 10)];
				Game.deck[j][(deck[j] / 2 + k)] = rand() % 7;//insert treature,estate,dutchy,province and curse into deck
			}
			shuffle(j, &Game);
			//randomize hand -> just draw 4 cards and put one more tribute into player's hand
			for (k = 0; k < Game.handCount[j]; k++) {
				Game.hand[j][k] = -1;
			}

			Game.handCount[j] = 0;

			for (k = 0; k < 4; k++) {
				drawCard(j, &Game);

			}

			Game.hand[j][Game.handCount[j]] = tribute;//insert a tribute to make sure that there is at least one minion in player's hand 
			Game.handCount[j]++;
			hand[j] = 5;

		}

		result = playCard(Game.handCount[0] - 1,0,0,0,&Game);//I call play_tribute here because I want to check tributeRevealedCards.
		Game.numActions--;
		updateCoins(Game.whoseTurn, &Game, bonus);//manually update these stuff in playcard()

		if (result == 0) {
			if (Game.numActions != 1 || Game.numActions!=0 || Game.numActions != 3) {
				errors += 1;
				fails += 1;
			}
			else if (Game.coins != preCoin[0] + 2 || Game.coins != preCoin[0] + 4 || Game.coins != preCoin[0]) {
				errors += 1;
				fails += 1;
			}
			else if (Game.handCount[0] != hand[0] || Game.handCount[0] != hand[0]+2 || Game.handCount[0] != hand[0]+4 ) {
				errors += 1;
				fails += 1;
			}
			else if ((tributeRevealedCards[0]<curse || tributeRevealedCards[0]>treasure_map) || (tributeRevealedCards[1]<curse || tributeRevealedCards[1]>treasure_map)) {
				errors += 1;
				fails += 1;
			}
			else if (Game.discardCount[0] != discard[0] + 1 && Game.discardCount[1] != 2) {
				errors += 1;
				fails += 1;
			}
			else {
				pass += 1;
				//printf("pass\n");
			}
		}
		else
			fails += 1;

	}

	printf("the number of passes are:%d\n", pass);
	printf("the number of fails are:%d\n", fails);
	printf("the number of errors are:%d\n", errors);

	return 0;
}
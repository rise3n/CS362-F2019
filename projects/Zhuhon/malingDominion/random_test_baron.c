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
	int i, j, k, num_of_player,errors=0, fails = 0, pass = 0, result, choice1;//fails is the number of failues due to random numbers.
	int deck[4] = { -1,-1,-1,-1 };//deck and hand save the randomized results of deck and hand count.
	int hand[4] = { -1,-1,-1,-1 };
	int preCoin[4] = { -1,-1,-1,-1 };
	int preEstate[4] = { -1,-1,-1,-1 };
	int discard[4] = { 0,0,0,0 };


	printf("start random test for baron\n");
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
			//randomize hand -> just draw 4 cards and put one more baron into player's hand
			for (k = 0; k < Game.handCount[j]; k++) {
				Game.hand[j][k] = -1;
			}

			Game.handCount[j] = 0;

			for (k = 0; k < 4; k++) {
				drawCard(j, &Game);

			}
			
			Game.hand[j][Game.handCount[j]] = baron;//insert a baron to make sure that there is at least one baron in player's hand 
			Game.handCount[j]++;
			hand[j] = 5;

			preCoin[j] = Game.coins;
			preEstate[j] = fullDeckCount(j, estate, &Game);

			//track down the number of coins and number of estates before baron is played.
		}

		choice1 = rand() % 2;//random choice for baron
		result = playCard(Game.handCount[0] - 1, choice1, 0, 0, &Game);

		if (result == 0) {
			if (Game.coins != preCoin[0] + 1 || Game.coins != preCoin[0] + 5) {
				errors += 1;
				fails += 1;
			}
			else if (fullDeckCount(0, estate, &Game) == preEstate[0]) {
				errors += 1;
				fails += 1;
			}
			else if (Game.discardCount[0] != 1 || Game.discardCount[0] != 2) {
				errors += 1;
				fails += 1;
			}
			else if (Game.handCount[0] != (hand[0] - 2) || Game.handCount[0] != hand[0]) {
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

	printf("the number of passes are:%d\n",pass);
	printf("the number of fails are:%d\n", fails);
	printf("the number of errors are:%d\n", errors);

	return 0;
}
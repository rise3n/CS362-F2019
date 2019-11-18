CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

random_test_baron: random_test_baron.c dominion.o rngs.o
	gcc  -o random_test_baron -g  random_test_baron.c dominion.o rngs.o $(CFLAGS)

random_test_minion: random_test_minion.c dominion.o rngs.o
	gcc  -o random_test_minion -g  random_test_minion.c dominion.o rngs.o $(CFLAGS)

random_test_tribute: random_test_tribute.c dominion.o rngs.o
	gcc  -o random_test_tribute -g  random_test_tribute.c dominion.o rngs.o $(CFLAGS)

randomtestresults: random_test_baron random_test_minion random_test_tribute	
	./random_test_baron &> randomtestresults.out
#	gcov -b -f dominion.c >> randomtestresults.out
	./random_test_minion >> randomtestresults.out
#	gcov -b -f dominion.c >> randomtestresults.out
	./random_test_tribute >> randomtestresults.out
	gcov -b -f dominion.c >> randomtestresults.out
	cat dominion.c.gcov >> randomtestresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe random_test_baron random_test_minion random_test_tribute

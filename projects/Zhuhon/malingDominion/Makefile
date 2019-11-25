CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

teammateDominion.o: dominion.h teammateDominion.c rngs.o
	gcc -c teammateDominion.c -g  $(CFLAGS)

playdom: teammateDominion.o playdom.c
	gcc -o playdom playdom.c -g teammateDominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c teammateDominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c teammateDominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

random_test_baron: random_test_baron.c teammateDominion.o rngs.o
	gcc  -o random_test_baron -g  random_test_baron.c teammateDominion.o rngs.o $(CFLAGS)

random_test_minion: random_test_minion.c teammateDominion.o rngs.o
	gcc  -o random_test_minion -g  random_test_minion.c teammateDominion.o rngs.o $(CFLAGS)

random_test_tribute: random_test_tribute.c teammateDominion.o rngs.o
	gcc  -o random_test_tribute -g  random_test_tribute.c teammateDominion.o rngs.o $(CFLAGS)

randomtestresults: random_test_baron random_test_minion random_test_tribute	
	./random_test_baron &> randomtestresults.out
	./random_test_minion >> randomtestresults.out
	./random_test_tribute >> randomtestresults.out
	gcov -b -f teammateDominion.c >> randomtestresults.out
	cat teammateDominion.c.gcov >> randomtestresults.out

unittest1: unittest1.c teammateDominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c teammateDominion.o rngs.o $(CFLAGS)

runtest1: unittest1
	./unittest1 &> unittestresult.out
	gcov -b -f teammateDominion.c >> unittestresult.out
	cat teammateDominion.c.gcov >> unittestresult.out

unittest2: unittest2.c teammateDominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c teammateDominion.o rngs.o $(CFLAGS)

runtest2: unittest2
	./unittest2 &> unittestresult.out
	gcov -b -f teammateDominion.c >> unittestresult.out
	cat teammateDominion.c.gcov >> unittestresult.out

unittest3: unittest3.c teammateDominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c teammateDominion.o rngs.o $(CFLAGS)

runtest3: unittest3
	./unittest3 &> unittestresult.out
	gcov -b -f teammateDominion.c >> unittestresult.out
	cat teammateDominion.c.gcov >> unittestresult.out

unittest4: unittest4.c teammateDominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c teammateDominion.o rngs.o $(CFLAGS)

runtest4: unittest4
	./unittest4 &> unittestresult.out
	gcov -b -f teammateDominion.c >> unittestresult.out
	cat teammateDominion.c.gcov >> unittestresult.out

unittest5: unittest5.c teammateDominion.o rngs.o
	gcc -o unittest5 -g  unittest5.c teammateDominion.o rngs.o $(CFLAGS)

runtest5: unittest5
	./unittest5 &> unittestresult.out
	gcov -b -f teammateDominion.c >> unittestresult.out
	cat teammateDominion.c.gcov >> unittestresult.out

runalltest: unittest1 unittest2 unittest3 unittest4 unittest5 
	./unittest1 &> unittestresult.out
	./unittest2 >> unittestresult.out
	./unittest3 >> unittestresult.out
	./unittest4 >> unittestresult.out
	./unittest5 >> unittestresult.out
	gcov -b -f teammateDominion.c >> unittestresult.out
	cat teammateDominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  teammateDominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe random_test_baron random_test_minion random_test_tribute

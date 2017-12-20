CC=g++
CFLAGS=-g -O0 -std=c++11

all:
	$(CC) $(CFLAGS) -c AllPair.cpp -o AllPair.o
	$(CC) $(CFLAGS) -c main.cpp -o main.o
	$(CC) $(CFLAGS) *.o -o allpair

clean :
	rm -f  *.o
	rm allpair

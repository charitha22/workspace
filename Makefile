CC=g++
CFLAGS=-g -O0 -std=c++11

all: allpair driver
	$(CC) $(CFLAGS) -c Graph.cpp -o Graph.o
	$(CC) $(CFLAGS) -c Common.cpp -o Common.o
	$(CC) $(CFLAGS) -c allpair.cpp -o allpair.o
	$(CC) $(CFLAGS) -c driver.cpp -o driver.o

allpair : allpair.o Graph.o 
	$(CC) $(CFLAGS) $^ -o $@

driver : driver.o Common.o
	$(CC) $(CFLAGS) $^ -o $@

clean :
	rm -f  *.o
	rm allpair driver

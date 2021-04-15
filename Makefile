CC=gcc
CFLAGS=-Wall -std=c99 -g 

start: compare.o bst.o queue.o game.o start.c
	$(CC) $(CFLAGS) compare.o bst.o queue.o game.o start.c -o start
	valgrind --leak-check=full --show-leak-kinds=all ./start

game.o: game.c game.h
	$(CC) $(CFLAGS) -c game.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c 

bst.o: bst.c bst.h
	$(CC) $(CFLAGS) -c bst.c

compare.o: compare.c 
	$(CC) $(CFLAGS) -c compare.c

clean:
	rm -f *.o
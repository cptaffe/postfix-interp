CFLAGS=-O1 -std=c11 -lm
CC=clang
BIN=post
SRC=main.c

primes:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

clean:
	rm $(BIN)
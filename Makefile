CFLAGS=-O1 -std=c11 -lm
CC=clang
BIN=post
SRC=main.c stack.c

primes:
	$(CC) $(CFLAGS) -o $(BIN) $(SRC)

clean:
	rm $(BIN)

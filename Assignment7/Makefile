CC=gcc
CFLAGS= -Wall -pedantic -g3
all: decrypt
decrypt: decrypt.c dictionary.h
	$(CC) $(CFLAGS) -o $@ $^
clean:
	rm *.o 

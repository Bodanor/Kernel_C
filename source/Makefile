CC=gcc
CFLAGS=-m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra

utils.o: utils.c ../include/utils.h
	$(CC) -c utils.c -o utils.o $(CFLAGS)

clean:
	rm -rf *.o
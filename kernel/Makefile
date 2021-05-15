CC=gcc
CFLAGS=-m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra

kernel.o: kernel.c kernel.h
	$(CC) -c kernel.c -o kernel.o $(CFLAGS)


clean:
	rm -rf *.o
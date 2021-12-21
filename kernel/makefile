CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding

kernel.bin: kernel.o
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

kernel.o: kernel.c
	$(CC) $(CCFLAGS) -c $^ -o $@

clean:
	rm *.o *.bin
	
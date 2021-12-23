C_SOURCES = $(wildcard ../drivers/*.c ../cpu/*.c ../libc/*.c)
HEADERS = $(wildcard ../drivers/*.h ../cpu/*.h ../libc/*.h)

OBJ = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
AS = /usr/local/i386elfgcc/bin/i386-elf-as

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding

kernel.bin: kernel_entry.o kernel.o $(OBJ) ../cpu/interrupt.o
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

kernel.o: kernel.c
	$(CC) $(CCFLAGS) -c $^ -o $@

util.o: util.c
	$(CC) $(CCFLAGS) -c $^ -o $@

kernel_entry.o: kernel_entry.S
	$(AS) $^ -o $@

debug: kernel_entry.o kernel.o $(OBJ) ../cpu/interrupt.o
	$(LD) -T linker.ld -o kernel.elf $^

$(OBJ):
	(cd ../drivers && make)
	(cd ../cpu && make)
	(cd ../libc && make)

clean:
	rm -rf *.o *.bin

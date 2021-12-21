C_SOURCES = $(wildcard ../drivers/*.c)
HEADERS = $(wildcard ../drivers/*.h)

OBJ = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
AS = /usr/local/i386elfgcc/bin/i386-elf-as

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding

kernel.bin: kernel_entry.o kernel.o $(OBJ)
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

kernel.o: kernel.c
	$(CC) $(CCFLAGS) -c $^ -o $@

kernel_entry.o: kernel_entry.S
	$(AS) $^ -o $@


$(OBJ):
	(cd ../drivers && make)


clean:
	rm *.o *.bin

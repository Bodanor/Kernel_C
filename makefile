C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
# Nice syntax for file extension replacement
OBJ = ${C_SOURCES:.c=.o}

# Change this if your cross-compiler is somewhere else
CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
GDB = gdb
# -g: Use debugging symbols in gcc
CFLAGS = -g

# First rule is run by default
os-image.bin: bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: kernel_entry.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x8000 $^ --oformat binary

bootsect.bin: boot.o
	ld -melf_i386 -T linker.ld --oformat binary boot.o -o bootsect.bin


boot.o: boot.S
	i386-elf-as --msyntax=intel -mnaked-reg -g boot.S -o boot.o

kernel.o: kernel.c
	i386-elf-gcc -ffreestanding -c kernel.c -o kernel.o

kernel_entry.o: kernel_entry.S
	i386-elf-as --msyntax=intel -mnaked-reg -g kernel_entry.S -o kernel_entry.o

kernel.elf: kernel_entry.o boot.o kernel.o
	i386-elf-ld -o $@ -Ttext 0x1000 $^ 
run: os-image.bin
	qemu-system-i386 -fda os-image.bin

# Open the connection to qemu and load our kernel-object file with symbols
debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

# Generic rules for wildcards
# To make an object, always compile from its .c

clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf *.o *.bin *.o *.o

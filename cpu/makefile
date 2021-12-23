C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJ = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
AS = /usr/local/i386elfgcc/bin/i386-elf-as

CCFLAGS = -ffreestanding

all: $(OBJ) interrupt.o

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@


interrupt.o : interrupt.S
	$(AS) $^ -o $@

clean:
	rm -rf *.o

C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJ = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc
LD = /usr/local/i386elfgcc/bin/i386-elf-ld
AS = /usr/local/i386elfgcc/bin/i386-elf-as

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding

all: $(OBJ)

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@


clean:
	rm *.o

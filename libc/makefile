C_SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

OBJ = ${C_SOURCES:.c=.o}

CC = /usr/local/i386elfgcc/bin/i386-elf-gcc

CCFLAGS = -ffreestanding

all: $(OBJ)

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@


clean:
	rm -rf *.o

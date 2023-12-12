CC = gcc
LD = ld

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding -m32 -fno-pie

C_SOURCES := $(wildcard *.c)
C_OBJECTS := $(C_SOURCES:.c=.o)
DEP := $(C_OBJECTS:%.o=%.d)

all:$(C_OBJECTS)

%.o:%.c
	$(info Building : $<)
	$(CC) $(CCFLAGS) -c $< -MD -MP -MF ${@:.o=.d} -o $@ 

-include $(DEP)

clean:
	rm -rf *.o
	rm -rf *.d
	

AS = i386-elf-as
CC = i386-elf-gcc
LD = i386-elf-ld

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding

AS_SRC := $(wildcard *.s)
AS_OBJ := $(AS_SRC:.s=.o)

C_SOURCES := $(wildcard *.c)
C_OBJECTS := $(C_SOURCES:.c=.o)
DEP := $(C_OBJECTS:%.o=%.d)

all:$(C_OBJECTS) $(AS_OBJ)

%.o:%.c
	$(info Building : $<)
	$(CC) $(CCFLAGS) -c $< -MD -MP -MF ${@:.o=.d} -o $@ $(addprefix -I , $(SUBDIRINCLUDE))


%.o:%.s
	$(AS) -o $@ $<

-include $(DEP)

clean:
	rm -rf *.o
	rm -rf *.d

AS = as
CC = gcc
LD = ld

LDFLAGS = --oformat binary
CCFLAGS = -ffreestanding -m32 -fno-pie

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
	$(AS) --32 -o $@ $<

-include $(DEP)

clean:
	rm -rf *.o
	rm -rf *.d

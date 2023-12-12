SUBDIRS := vga

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

.PHONY: all $(SUBDIRS)

all:$(SUBDIRS) $(C_OBJECTS) $(AS_OBJ)


%.o:%.c
	$(info Building : $<)
	$(CC) $(CCFLAGS) -c $< -MD -MP -MF ${@:.o=.d} -o $@ $(addprefix -I , $(SUBDIRINCLUDE))


%.o:%.s
	$(AS) --32 -o $@ $<

-include $(DEP)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	@$(MAKE) -C vga clean
	rm -rf *.o
	rm -rf *.d
	

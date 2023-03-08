SUBDIRS := vga

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

.PHONY: all $(SUBDIRS)

all:$(SUBDIRS) $(C_OBJECTS) $(AS_OBJ)


%.o:%.c
	$(info Building : $<)
	$(CC) $(CCFLAGS) -c $< -MD -MP -MF ${@:.o=.d} -o $@ $(addprefix -I , $(SUBDIRINCLUDE))


%.o:%.s
	$(AS) -o $@ $<

-include $(DEP)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	@$(MAKE) -C vga clean
	rm -rf *.o
	rm -rf *.d
	

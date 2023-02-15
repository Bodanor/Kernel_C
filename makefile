SUBDIRSKERNEL := kernel
SUBDIRBOOTLOADER := bootloader-mbr

C_SOURCES := $(wildcard $(SUBDIRSKERNEL)/*.c)
C_OBJECTS := $(C_SOURCES:.c=.o)

LD = i386-elf-ld
LDFLAGS = --oformat binary -T linker.ld

all: $(SUBDIRBOOTLOADER) $(SUBDIRSKERNEL) kernel.bin

$(SUBDIRSKERNEL):
	@$(MAKE) -C $@

$(SUBDIRBOOTLOADER):
	@$(MAKE) -C $@

kernel.bin: $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(C_OBJECTS)


.PHONY: all $(SUBDIRBOOTLOADER) $(SUBDIRSKERNEL)
clean:
	@$(MAKE) -C bootloader-mbr clean
	@$(MAKE) -C kernel clean
	rm -rf kernel.bin

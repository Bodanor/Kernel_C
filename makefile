MAKEDIR := $(shell pwd)

SUBDIRSKERNEL := $(MAKEDIR)/kernel $(MAKEDIR)/drivers $(MAKEDIR)/cpu
SUBDIRBOOTLOADER := bootloader-mbr


SUBDIRINCLUDE := $(shell find $(SUBDIRSKERNEL) -type d )
C_SOURCES := $(shell find $(SUBDIRSKERNEL) -name '*.c')
C_OBJECTS := $(C_SOURCES:.c=.o)

IMGDIR = IMG
LD = i386-elf-ld
LDFLAGS = --oformat binary -T linker.ld

export SUBDIRINCLUDE

all: $(SUBDIRBOOTLOADER) $(SUBDIRSKERNEL) KERNEL.BIN

$(SUBDIRSKERNEL):
	@$(MAKE) -C $@

$(SUBDIRBOOTLOADER):
	@$(MAKE) -C $@

KERNEL.BIN: $(C_OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(C_OBJECTS)

image:
	mkdir -p $(IMGDIR)
	dd if=/dev/zero of=$(IMGDIR)/hdd.img bs=516096c count=20
	(echo o;echo n; echo p; echo 1; echo; echo; echo t; echo 6; echo a; echo p; echo w) | fdisk -u -C1000 -S63 -H16 $(IMGDIR)/hdd.img
	dd if=bootloader-mbr/mbr/mbr of=$(IMGDIR)/hdd.img bs=446 count=1 conv=notrunc
	sudo losetup -o 1048576 /dev/loop0 $(IMGDIR)/hdd.img
	sudo mkfs.fat -F16 -v /dev/loop0 -h 0x800
	sudo dd if=bootloader-mbr/vbr/vbr-bootloader of=/dev/loop0 bs=1 count=3 conv=notrunc
	sudo dd if=bootloader-mbr/vbr/vbr-bootloader of=/dev/loop0 bs=1 skip=62 seek=62 conv=notrunc
	sudo mount /dev/loop0 /mnt
	cp KERNEL.BIN /mnt/
	sudo umount /mnt
	sudo losetup -d /dev/loop0	

.PHONY: all $(SUBDIRBOOTLOADER) $(SUBDIRSKERNEL)
clean:
	@$(MAKE) -C bootloader-mbr clean
	@$(MAKE) -C kernel clean
	@$(MAKE) -C drivers clean
	@$(MAKE) -C cpu clean
	rm -rf KERNEL.BIN
	rm -rf IMG/*

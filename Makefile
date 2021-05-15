KERNELVER=0.0.1

AS=as
ASFLAGS= --32
LD=ld
LDFLAGS=-m elf_i386 -nostdlib

BIN=kernel_$(KERNELVER).bin
ISO=kernel_$(KERNELVER).iso
ISO_PATH=kernel_$(KERNELVER)_qemu
BOOT_PATH=$(ISO_PATH)/boot
GRUB_PATH=$(BOOT_PATH)/grub

.PHONY : kernel/kernel.o source/utils.o


all: boot.o kernel/kernel.o source/utils.o $(BIN) iso
	@echo Make has completed.

boot.o: boot/boot.s
	$(AS) boot/boot.s -o boot.o $(ASFLAGS)

kernel/kernel.o:
	(cd kernel; make)
	
source/utils.o:
	(cd source; make)


$(BIN): linker.ld boot.o kernel/kernel.o source/utils.o
	$(LD) -T linker.ld kernel/kernel.o source/utils.o boot.o -o $(BIN) $(LDFLAGS)

iso grub/grub.cfg:
	mkdir -p $(GRUB_PATH)
	cp $(BIN) $(BOOT_PATH)
	cp grub/grub.cfg $(GRUB_PATH)
	grub-mkrescue -o $(ISO) $(ISO_PATH)



clean:
	rm -rf *.o $(BIN) $(ISO_PATH)
	(cd kernel;make clean)
	(cd source; make clean)
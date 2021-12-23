
all: Kernel-0.iso

Kernel-0.iso: bootloader/bootloader.bin kernel/kernel.bin
	cat bootloader/bootloader.bin kernel/kernel.bin > $@

bootloader/bootloader.bin:
	(cd bootloader && make)

kernel/kernel.bin:
	(cd kernel && make)


run: Kernel-0.iso
	qemu-system-i386 -fda $^

debug:
	(cd kernel && make debug)
	(cd bootloader && make debug)
	cat bootloader/bootloader.elf kernel/kernel.elf > os-image.elf
	qemu-system-i386 -s -fda Kernel-0.iso & gdb -ex "target remote localhost:1234" -ex "symbol-file os-image.elf"
	
clean:
	(cd kernel && make clean)
	(cd bootloader && make clean)
	(cd drivers && make clean)
	(cd cpu && make clean)
	rm -rf *.iso
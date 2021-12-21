
Kernel-0.iso: bootloader/bootloader.bin kernel/kernel.bin
	cat bootloader/bootloader.bin kernel/kernel.bin > $@

bootloader/bootloader.bin:
	(cd bootloader && make)

kernel/kernel.bin:
	(cd kernel && make)

run: Kernel-0.iso
	qemu-system-x86_64 -fda $^

clean:
	(cd kernel && make clean)
	(cd bootloader && make clean)
	rm *.iso
include targets.mk

kernel-0.iso : boot/bootloader.bin kernel/kernel.bin
	cat boot/bootloader.bin kernel/kernel.bin > $@


boot/bootloader.bin:
	(cd boot && make)

kernel/kernel.bin:
	(cd kernel && make)

run: kernel-0.iso
	qemu-system-i386 -fda $^


debug: kernel-0.iso
	bochs -q -f .bochsrc.txt

clean :
	(cd boot && make clean)
	(cd kernel && make clean)
	rm -rf *.o *iso

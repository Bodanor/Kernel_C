AS=i386-elf-as
LD=i386-elf-ld
LDFLAGS=--oformat binary -T linker.ld

SOURCES := $(wildcard *.s)
OBJECTS := $(patsubst %.s, %.o, $(SOURCES))

bootloader.bin : $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

run: bootloader.bin
	qemu-system-x86_64 $^

debug: bootloader.bin
	bochs -q -f .bochsrc.txt
%.o: %.s
	$(AS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf bootloader.bin
	rm -rf bx_enh_dbg.ini
	rm -rf zygomatic.log


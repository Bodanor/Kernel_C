AS = /usr/local/i386elfgcc/bin/i386-elf-as
LD = /usr/local/i386elfgcc/bin/i386-elf-ld

LDFLAGS = --oformat binary

bootloader.bin : boot.o
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^


boot.o : boot.S
	$(AS) $^ -o $@

debug: boot.o
	$(LD)  -T linker.ld -o bootloader.elf $^

clean:
	rm -rf *.o *bin

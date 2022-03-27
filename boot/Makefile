include ../targets.mk

INPUTS = $(wildcard *.S)



bootloader.bin: boot.o
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

boot.o:	$(INPUTS)
	$(AS) boot.S -o $@

clean:
	rm -rf *.o *bin
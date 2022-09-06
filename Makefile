AS=i386-elf-as
LD=i386-elf-ld
LDFLAGS=--oformat binary -T linker.ld

SOURCES := $(wildcard *.s)
OBJECTS := $(patsubst %.s, %.o, $(SOURCES))

bootloader.bin : $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

%.o: %.s
	$(AS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf bootloader.bin



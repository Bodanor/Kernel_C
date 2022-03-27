include ../targets.mk

kernel.bin : kernel.o
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $^

kernel.o: kernel.c
	$(GCC) $(CCFLAGS) -c $^ -o $@


clean:
	rm -rf *.o *.bin
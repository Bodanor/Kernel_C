SUBDIRSKERNEL := kernel
SUBDIRBOOTLOADER := bootloader-mbr

all: $(SUBDIRBOOTLOADER) $(SUBDIRSKERNEL)

$(SUBDIRSKERNEL):
	@$(MAKE) -C $@

$(SUBDIRBOOTLOADER):
	@$(MAKE) -C $@


.PHONY: all $(SUBDIRBOOTLOADER) $(SUBDIRSKERNEL)
clean:
	@$(MAKE) -C bootloader-mbr clean
	@$(MAKE) -C kernel clean

SUBDIRS := vga


.PHONY: all $(SUBDIRS)

all:$(SUBDIRS)

$(SUBDIRS):
	@$(MAKE) -C $@

clean:
	@$(MAKE) -C vga clean
	

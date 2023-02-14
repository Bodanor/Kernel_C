SUBDIRS := bootloader-mbr

BUILD_DIR := build
MAKE_DIR := $(pwd)

all: $(SUBDIRS)

$(SUBDIRS):
	mkdir -p $(BUILD_DIR)
	@$(MAKE) -C $@

image: $(SUBDIRS)
	dd if=/dev/zero of=$(BUILD_DIR)/hdd.img bs=516096c count=20
	(echo o;echo n; echo p; echo 1; echo; echo; echo t; echo 6; echo a; echo p; echo w) | fdisk -u -C1000 -S63 -H16 $(BUILD_DIR)/hdd.img
	dd if=mbr/mbr of=$(BUILD_DIR)/hdd.img bs=446 count=1 conv=notrunc
	sudo losetup -o 1048576 /dev/loop0 $(BUILD_DIR)/hdd.img
	sudo mkfs.fat -F16 -v /dev/loop0 -h 0x800
	sudo dd if=vbr/vbr-bootloader of=/dev/loop0 bs=1 count=3 conv=notrunc
	sudo dd if=vbr/vbr-bootloader of=/dev/loop0 bs=1 skip=62 seek=62 conv=notrunc
	sudo mount /dev/loop0 /mnt
	sudo touch /mnt/KERNEL.BIN
	sudo dd if=/dev/random of=/mnt/KERNEL.BIN bs=1 count=3000
	sudo umount /mnt
	sudo losetup -d /dev/loop0	

.PHONY: all $(SUBDIRS) clean

clean:
	@$(MAKE) -C bootloader-mbr clean
	rm -rf $(BUILD_DIR)/* 

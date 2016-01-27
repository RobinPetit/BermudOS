CC=i686-elf-gcc
C_FLAGS=-std=gnu99 -ffreestanding -O2
LINKER_FILE=boot/linker.ld
OS_NAME=BermudOS
OBJECTS=$(wildcard kernel/obj/**/*.o) $(wildcard kernel/obj/*.o) $(wildcard boot/**/*.o) $(wildcard io/**/*.o) $(wildcard io/*.o)

iso: link
	rm -f boot/iso/boot/$(OS_NAME).iso
	cp $(OS_NAME).bin boot/iso/boot/$(OS_NAME).bin
	grub-mkrescue -o $(OS_NAME).iso boot/iso

link: boot kernel io
	$(CC) -T $(LINKER_FILE) -o $(OS_NAME).bin $(C_FLAGS) -nostdlib $(OBJECTS) -lgcc

boot:
	make -C boot/

kernel:
	make -C kernel/

io:
	make -C io/

clean:
	make -C boot/ clean
	make -C kernel/ clean
	make -C io/ clean

.PHONY: boot kernel io

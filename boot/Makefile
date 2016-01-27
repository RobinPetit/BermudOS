AS=nasm
CC=i686-elf-gcc
AS_FORMAT=elf32
AS_FILES=$(wildcard *.asm)
AS_OBJS=$(patsubst %.asm, ASMOBJ/%.o, $(AS_FILES))
C_FILES=$(wildcard *.c)
C_OBJS=$(patsubst %.c, COBJ/%.o, $(C_FILES))
LINKER_FILE=linker.ld
C_FLAGS=-std=gnu99 -ffreestanding -O2
C_FLAGS_WARNINGS=-Wall -Wextra
OS_NAME=BermudOS

link: CC asm
	$(CC) -T $(LINKER_FILE) -o $(OS_NAME).bin $(C_FLAGS) -nostdlib $(AS_OBJS) $(C_OBJS) -lgcc

asm: $(AS_OBJS)

CC: $(C_OBJS)

ASMOBJ/%.o: %.asm
	$(AS) -f$(AS_FORMAT) $< -o $@

COBJ/%.o: %.c
	$(CC) -c $< -o $@ $(C_FLAGS) $(C_FLAGS_WARNINGS)

iso: link
	rm -f iso/boot/$(OS_NAME).iso
	cp $(OS_NAME).bin iso/boot/$(OS_NAME).bin
	grub-mkrescue -o $(OS_NAME).iso iso

clean:
	rm -f ASMOBJ/*
	rm -f COBJ/*
	rm -f $(OS_NAME).bin

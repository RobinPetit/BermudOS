AS=nasm
CC=i686-elf-gcc
AS_FORMAT=elf32
AS_FILES=$(wildcard *.asm)
AS_OBJS=$(patsubst %.asm, ASMOBJ/%.o, $(AS_FILES))
C_FILES=$(wildcard *.c)
C_OBJS=$(patsubst %.c, COBJ/%.o, $(C_FILES))
C_FLAGS=-std=gnu99 -ffreestanding -O2 -I ../include/BermudOS
C_FLAGS_WARNINGS=-Wall -Wextra

all: CC asm

asm: $(AS_OBJS)

CC: $(C_OBJS)

ASMOBJ/%.o: %.asm
	$(AS) -f$(AS_FORMAT) $< -o $@

COBJ/%.o: %.c
	$(CC) -c $< -o $@ $(C_FLAGS) $(C_FLAGS_WARNINGS)

clean:
	rm -f $(AS_OBJS)
	rm -f $(C_OBJS)

AS=nasm
FORMAT=elf32
AS_FILES=$(wildcard *.asm)
AS_OBJS=$(patsubst %.asm, ASMOBJ/%.o, $(AS_FILES))

asm_boot: $(AS_OBJS)

ASMOBJ/%.o: %.asm
	$(AS) -f$(FORMAT) $< -o $@

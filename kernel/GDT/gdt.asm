extern gdt_location
global gdt_flush

%define CODE_SEGMENT 0x10
%define DATA_SEGMENT 0x08

section .text
gdt_flush:
	lgdt [gdt_location]
	mov ax, DATA_SEGMENT
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp CODE_SEGMENT:end_gdt_flush
end_gdt_flush:
	ret

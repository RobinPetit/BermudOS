global isr_management
extern fault_handler

%define CODE_SEGMENT 0x10
%define DATA_SEGMENT 0x08

section .text
isr_management:
    ; save registers
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, DATA_SEGMENT
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	; Save the stack onto the stack (parameter to fault_handler)
	mov eax, esp
	push eax
	mov eax, fault_handler
	call eax  ; A special call, preserves the 'eip' register
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8  ; Cleans up the pushed error code and pushed ISR number
	; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!
	iret

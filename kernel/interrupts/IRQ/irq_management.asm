global irq_management
extern irq_handler

%define CODE_SEGMENT 0x10
%define DATA_SEGMENT 0x08

section .text
irq_management:
	; set the stack correctly for interrupt_stack_state
	pusha
	push ds
	push es
	push fs
	push gs
	; stack is set correctly

	mov ax, DATA_SEGMENT  ; eax is save by pusha
	; set DATA_SEGMENT for every segment register
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov eax, esp  ; save the stack...
	push eax  ; ... onto the stack (parameter to irq_handler)
	mov eax, irq_handler
	call eax  ; special call: preserves the 'eip' register
	pop eax

	; restore stack
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8  ; remove the interrupt informations
	iret  ; return from interrupt

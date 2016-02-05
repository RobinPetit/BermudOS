extern isr_management
global isr20

section .text
isr20:
	cli
	push byte 0
	push byte 20

	jmp isr_management



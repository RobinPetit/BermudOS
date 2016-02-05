extern isr_management
global isr13

section .text
isr13:
	cli
	push byte 13

	jmp isr_management



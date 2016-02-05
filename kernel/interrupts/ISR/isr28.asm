extern isr_management
global isr28

section .text
isr28:
	cli
	push byte 0
	push byte 28

	jmp isr_management



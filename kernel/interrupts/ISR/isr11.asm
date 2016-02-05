extern isr_management
global isr11

section .text
isr11:
	cli
	push byte 11

	jmp isr_management



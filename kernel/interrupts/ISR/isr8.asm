extern isr_management
global isr8

section .text
isr8:
	cli
	push byte 8

	jmp isr_management



extern isr_management
global isr26

section .text
isr26:
	cli
	push byte 0
	push byte 26

	jmp isr_management



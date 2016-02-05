extern isr_management
global isr25

section .text
isr25:
	cli
	push byte 0
	push byte 25

	jmp isr_management



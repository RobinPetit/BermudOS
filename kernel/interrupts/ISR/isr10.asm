extern isr_management
global isr10

section .text
isr10:
	cli
	push byte 10

	jmp isr_management



extern isr_management
global isr27

section .text
isr27:
	cli
	push byte 0
	push byte 27

	jmp isr_management



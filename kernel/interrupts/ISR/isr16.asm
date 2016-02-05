extern isr_management
global isr16

section .text
isr16:
	cli
	push byte 0
	push byte 16

	jmp isr_management



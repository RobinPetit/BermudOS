extern isr_management
global isr30

section .text
isr30:
	cli
	push byte 0
	push byte 30

	jmp isr_management



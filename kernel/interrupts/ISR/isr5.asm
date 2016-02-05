extern isr_management
global isr5

section .text
isr5:
	cli
	push byte 0
	push byte 5

	jmp isr_management



extern isr_management
global isr22

section .text
isr22:
	cli
	push byte 0
	push byte 22

	jmp isr_management



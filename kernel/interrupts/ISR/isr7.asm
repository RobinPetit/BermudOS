extern isr_management
global isr7

section .text
isr7:
	cli
	push byte 0
	push byte 7

	jmp isr_management



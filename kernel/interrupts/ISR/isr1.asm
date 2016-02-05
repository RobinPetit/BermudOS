extern isr_management
global isr1

section .text
isr1:
	cli
	push byte 0
	push byte 1

	jmp isr_management



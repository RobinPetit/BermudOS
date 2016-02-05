extern isr_management
global isr9

section .text
isr9:
	cli
	push byte 0
	push byte 9

	jmp isr_management



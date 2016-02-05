extern isr_management
global isr0

section .text
isr0:
	cli
	push byte 0
	push byte 0

	jmp isr_management



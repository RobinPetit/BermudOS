extern isr_management
global isr19

section .text
isr19:
	cli
	push byte 0
	push byte 19

	jmp isr_management



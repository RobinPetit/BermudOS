extern isr_management
global isr29

section .text
isr29:
	cli
	push byte 0
	push byte 29

	jmp isr_management



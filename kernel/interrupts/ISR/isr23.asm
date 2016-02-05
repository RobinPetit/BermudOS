extern isr_management
global isr23

section .text
isr23:
	cli
	push byte 0
	push byte 23

	jmp isr_management



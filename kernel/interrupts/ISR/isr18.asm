extern isr_management
global isr18

section .text
isr18:
	cli
	push byte 0
	push byte 18

	jmp isr_management



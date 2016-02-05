extern isr_management
global isr24

section .text
isr24:
	cli
	push byte 0
	push byte 24

	jmp isr_management



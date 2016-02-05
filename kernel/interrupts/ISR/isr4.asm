extern isr_management
global isr4

section .text
isr4:
	cli
	push byte 0
	push byte 4

	jmp isr_management



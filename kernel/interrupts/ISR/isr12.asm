extern isr_management
global isr12

section .text
isr12:
	cli
	push byte 0
	push byte 12

	jmp isr_management



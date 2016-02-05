extern isr_management
global isr15

section .text
isr15:
	cli
	push byte 0
	push byte 15

	jmp isr_management



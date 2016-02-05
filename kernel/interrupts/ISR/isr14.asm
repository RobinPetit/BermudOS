extern isr_management
global isr14

section .text
isr14:
	cli
	push byte 14

	jmp isr_management



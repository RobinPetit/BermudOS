extern isr_management
global isr21

section .text
isr21:
	cli
	push byte 0
	push byte 21

	jmp isr_management



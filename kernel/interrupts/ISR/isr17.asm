extern isr_management
global isr17

section .text
isr17:
	cli
	push byte 0
	push byte 17

	jmp isr_management



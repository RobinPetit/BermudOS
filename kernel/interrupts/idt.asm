extern idt_locate
global idt_load_asm

idt_load_asm:
	lidt [idt_location]
	ret

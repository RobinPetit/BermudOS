set(SOURCES
        "interrupts/APIC/apic.c"
		"interrupts/idt.c"
        #
        "MSR/MSR.c"
        #
        "terminal/terminal.c"
        #
        "video/VGA_management.c"
		#
		"GDT/gdt.c"
		"GDT/gdt.asm"
    )

add_library(kernel ${SOURCES})


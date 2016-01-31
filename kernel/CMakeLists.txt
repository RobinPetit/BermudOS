set(SOURCES
        "interrupts/APIC/apic.c"
        #
        "MSR/MSR.c"
        #
        terminal/terminal.c
        #
        video/VGA_management.c
    )

add_library(kernel ${SOURCES})


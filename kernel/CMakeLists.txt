set(C_SOURCES
	"memcpy.c"
	"memset.c"
	"video/VGA_management.c"
	"terminal/terminal.c"
	)

set(ASM_SOURCES "")

add_library(kernel ${C_SOURCES} ${ASM_SOURCES})


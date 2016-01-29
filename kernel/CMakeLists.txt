set(SOURCES
	"memcpy.c"
	"memset.c"
	"video/VGA_management.c"
	"terminal/terminal.c"
	)

add_library(kernel ${SOURCES})


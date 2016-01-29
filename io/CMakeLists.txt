set(C_SOURCES
	"in.c"
	"out.c"
	)
set(ASM_SOURCES "")

add_library(io ${C_SOURCES} ${ASM_SOURCES})


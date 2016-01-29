#if defined (__cplusplus)
 #error "Must be compiled as C code!"
#endif
#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

/* Only compiler-specific headers can be included */
#include "../kernel/terminal/terminal.h"
#include <stdio.h>

struct terminal_s terminal;

void kernel_main(void)
{
	terminal_init();
	puts("This is BermudOS with puts!");
	printf("This is BermudOS with printf!\n");
	printf("format is %%X %%x %%d %%i %%o... and result is %X %x %d %i %o\n",
	       256, 256, 256, 256, 256);
}


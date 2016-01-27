#if defined (__cplusplus)
 #error "Must be compiled as C code!"
#endif
#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

/* Only compiler-specific headers can be included */
#include "terminal.h"

struct terminal_s terminal;

void kernel_main(void)
{
	terminal_init();
	terminal_putstring("Hello World!\nAnd on a new line!");
}


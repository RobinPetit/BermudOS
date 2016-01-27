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
	int i;
	terminal_init();
	for(i = 0; i < 8; ++i)
		terminal_putstring("abcdefghijklmnopqrstuvwxyzzyxwvutsrqponmlkjihgfedcba\nABCDEFGHIJKLMNOPQRSTUVWXYZZYXWVUTSRQPONMLKJIHGFEDCBA\n01234567899876543210\n");
	terminal_put_entry_at('d', terminal.colour, VGA_WIDTH/2, VGA_HEIGHT-1);
	terminal_scroll_down();
}


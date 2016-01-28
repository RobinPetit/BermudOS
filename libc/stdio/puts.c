#include <stdio.h>
#include "../../kernel/terminal/terminal.h"

int puts(const char * restrict str)
{
	terminal_putstring(str);
	putchar('\n');
	return 1;
}

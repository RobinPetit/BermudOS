#include <stdio.h>
#include "../../kernel/terminal/terminal.h"

int putchar(int c)
{
	terminal_putchar(c);
	return c;
}

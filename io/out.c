#include "out.h"

void outb(uint16_t port, BYTE value)
{
	__asm__ __volatile__ ("outb %1, %0"
	                      :
						  : "dN" (port), "a" (value));
}

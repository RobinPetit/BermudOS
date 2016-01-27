#include "in.h"

BYTE inb(uint16_t port)
{
	BYTE ret;
	__asm__ __volatile__("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

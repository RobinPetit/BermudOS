#if defined (__cplusplus)
 #error "Must be compiled as C code!"
#endif
#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

/* Only compiler-specific headers can be included */
#include <stdio.h>
#include <string.h>
#include "../kernel/terminal/terminal.h"
#include "../kernel/interrupts/APIC/apic.h"
#include "../kernel/MSR/MSR.h"
#include "../kernel/GDT/gdt.h"
#include "../kernel/interrupts/idt.h"
#include "../kernel/interrupts/ISR/isr.h"
#include "../kernel/interrupts/IRQ/irq.h"
#include <div64.h>

struct terminal_s terminal;

void test_string_h(void)
{
	char buffer[64];
	strcpy(buffer, "This is BermudOS!");
	puts(buffer);
	strncpy(buffer, "This is BermudOS! Or is it?", 17);
	puts(buffer);
	strcat(buffer, " Version 0.1");
	puts(buffer);
	puts(strpbrk(buffer, " "));
	char *sub = strstr(buffer, "Version");
	if(sub == NULL)
		puts("NULL STRING!");
	else
		puts(sub);
	char *token = strtok(buffer, " ");
	while(token != NULL)
	{
		puts(token);
		token = strtok(NULL, " ");
	}
}

bool test_sprintf(void)
{
	char buffer[512] = "";
	bool ret;
	sprintf(buffer, "%c %s %2c %-2c %10s %-10s %10.2s",
	        'a', "to copy", 'c', 'c', "str", "str", "str");
	ret = strcmp(buffer, "a to copy  c c         str str                st") == 0;
	sprintf(buffer, "%d %x %#x %i %#07o", 24, 16, 32, 0, 65535);
	ret = ret && strcmp (buffer, "24 10 0x20 0 00177777") == 0;
	return ret;
}

bool test_div64(void)
{
	uint64_t dividend = 0xFFEEFFEEFFEEFFEEULL;
	uint32_t divisor  = 0xFFEEFFEE;
	uint32_t remainder = do_div(dividend, divisor);
	return dividend == 0x0000000100000001 && remainder == 0;
}

void kernel_main(void)
{
	terminal_init();
	puts("This is BermudOS with puts!");
	printf("This is BermudOS with printf!\n");
	printf("format is %%X %%x %%d %%i %%o... and result is %X %x %d %i %o\n",
	       256, 256, 256, 256, 256);
	// test_string_h();
	puts(test_sprintf() ? "sprintf IS working" : "sprint IS NOT working");
	puts(test_div64() ? "div64 IS working" : "div64 IS NOT wirking");
	puts(is_apic_compatible() ? "HARDWARE IS APIC COMPATIBLE" : "HARDWARE IS NOT APIC COMPATIBLE");
	puts(has_MSR() ? "CPU HAS MSR" : "CPU HAS NO MSR");
	puts(gdt_setup() ? "GDT setup correctly" : "Error while setting up GDT");
	puts(idt_setup() ? "IDT setup correctly" : "Error while setting up IDT");
	puts(isrs_setup() ? "ISRs setup correctly" : "Error while setting up ISRs");
	puts(irq_setup() ? "IRQs setup correctly" : "Error while setting up IRQs");
	__asm__ __volatile__("INT $0x00");
}


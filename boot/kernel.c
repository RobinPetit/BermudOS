#if defined (__cplusplus)
 #error "Must be compiled as C code!"
#endif
#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

/* Only compiler-specific headers can be included */
#include "../kernel/terminal/terminal.h"
#include <stdio.h>
#include <string.h>
#include "../kernel/interrupts/APIC/apic.h"
#include "../kernel/MSR/MSR.h"
#include "../kernel/GDT/gdt.h"

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

void kernel_main(void)
{
	terminal_init();
	puts("This is BermudOS with puts!");
	printf("This is BermudOS with printf!\n");
	printf("format is %%X %%x %%d %%i %%o... and result is %X %x %d %i %o\n",
	       256, 256, 256, 256, 256);
	test_string_h();
	puts(is_apic_compatible() ? "HARDWARE IS APIC COMPATIBLE" : "HARDWARE IS NOT APIC COMPATIBLE");
	puts(has_MSR() ? "CPU HAS MSR" : "CPU HAS NO MSR");
	puts(gdt_setup() ? "GDT setup correctly" : "Error while setting up GDT");
}


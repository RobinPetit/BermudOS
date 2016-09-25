#include "keyboard.h"
#include "../interrupts/IRQ/irq.h"
#include "../../io/in.h"

/* static prototypes */
static void keyboard_handler(struct interrupt_stack_state *);

static const char scancodes[KEYBOARD_SIZE] = 
{
	0,	/* None */
	0,	/* Esc */
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	')',
	'-',
	'\b',	/* Back */
	'\t',	/* Tab" */
	'a',
	'z',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'^',
	'$',
	'\n',	/* Enter */
	0,	/* Ctrl */
	'q',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	'm',
	'%',
	0,	/* ² */
	0,	/* Left Shift */
	'`',
	'w',
	'x',
	'c',
	'v',
	'b',
	'n',
	',',
	';',
	':',
	'=',
	0,	/* Right Shift */
	'*',	/* NumPad */
	0,	/* Alt */
	' ',	/* Whitespace */
	0,	/* Caps Lock */
	0,	/* F1 */
	0,	/* F2 */
	0,	/* F3 */
	0,	/* F4 */
	0,	/* F5 */
	0,	/* F6 */
	0,	/* F7 */
	0,	/* F8 */
	0,	/* F9 */
	0,	/* F10 */
	0,	/* Num Lock */
	0,	/* UNKNOWN YET: 71 */
	'7',	/* NumPad */
	'8',	/* NumPad */
	'9',	/* NumPad */
	'-',	/* NumPad */
	'4',	/* NumPad */
	'5',	/* NumPad */
	'6',	/* NumPad */
	'+',	/* NumPad */
	'1',	/* NumPad */
	'2',	/* NumPad */
	'3',	/* NumPad */
	'0',	/* NumPad */
	'.',	/* NumPad */
	0,	/* UNKNOWN YET: 84 */
	0,	/* UNKNOWN YET: 85 */
	'<',
	0,	/* F11 */
	0,	/* F12 */
	0,	/* UNKNOWN YET: 89 */
	0,	/* UNKNOWN YET: 90 */
	0,	/* Windows key */
	0,	/* UNKNOWN YET: 92 */
	0,	/* Right Click menu key */
	0,	/* UNKNOWN YET: 94 */
	0,	/* UNKNOWN YET: 95 */
	0,	/* UNKNOWN YET: 96 */
	0,	/* UNKNOWN YET: 97 */
	0,	/* UNKNOWN YET: 98 */
	0,	/* UNKNOWN YET: 99 */
	0,	/* UNKNOWN YET: 100 */
	0,	/* UNKNOWN YET: 101 */
	0,	/* UNKNOWN YET: 102 */
	0,	/* UNKNOWN YET: 103 */
	0,	/* UNKNOWN YET: 104 */
	0,	/* UNKNOWN YET: 105 */
	0,	/* UNKNOWN YET: 106 */
	0,	/* UNKNOWN YET: 107 */
	0,	/* UNKNOWN YET: 108 */
	0,	/* UNKNOWN YET: 109 */
	0,	/* UNKNOWN YET: 110 */
	0,	/* UNKNOWN YET: 111 */
	0,	/* UNKNOWN YET: 112 */
	0,	/* UNKNOWN YET: 113 */
	0,	/* UNKNOWN YET: 114 */
	0,	/* UNKNOWN YET: 115 */
	0,	/* UNKNOWN YET: 116 */
	0,	/* UNKNOWN YET: 117 */
	0,	/* UNKNOWN YET: 118 */
	0,	/* UNKNOWN YET: 119 */
	0,	/* UNKNOWN YET: 120 */
	0,	/* UNKNOWN YET: 121 */
	0,	/* UNKNOWN YET: 122 */
	0,	/* UNKNOWN YET: 123 */
	0,	/* UNKNOWN YET: 124 */
	0,	/* UNKNOWN YET: 125 */
	0,	/* UNKNOWN YET: 126 */
	0	/* UNKNOWN YET: 127 */
};

int keyboard_setup(void)
{
	return set_irq(1, keyboard_handler);
}

static int is_key_released(uint8_t scancode)
{
	return scancode & 0x80;
}

static void keyboard_handler(struct interrupt_stack_state *registers)
{
	uint8_t input_scancode = inb(PS2_DATA_REGISTER);
	if(is_key_released(input_scancode))
	{
		;
	}
	else
	{
		if(scancodes[input_scancode] != 0)
			putchar(scancodes[input_scancode]);
		else
			putchar('_');
	}
}

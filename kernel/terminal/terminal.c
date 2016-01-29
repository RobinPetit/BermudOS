#include <string.h>
#include "terminal.h"
#include "../../io/out.h"

static VGA_entry_t empty_cell;

/** static functions prototypes **/

static void terminal_move_cursor(int, int);

/** code **/

void terminal_init(void)
{
	terminal.row = terminal.column = 0;
	terminal.colour = make_colour(COLOUR_WHITE, COLOUR_BLACK);
	terminal.buffer = (VGA_entry_t *)(VGA_BUFFER_ADDRESS);
	terminal.writing = false;

	empty_cell = make_VGA_entry(' ', terminal.colour);

	terminal_clear_screen();
}

void terminal_set_colour(colour_t colour)
{
	terminal.colour = colour;
	empty_cell = make_VGA_entry(' ', terminal.colour);
}

void terminal_put_entry_at(char c, colour_t colour, size_t x, size_t y)
{
	terminal.buffer[VGA_COORD_TO_IDX(x, y)] = make_VGA_entry(c, colour);
}

void terminal_new_line(void)
{
	terminal.column = 0;
	++terminal.row;
	if(terminal.row == VGA_HEIGHT)
		terminal_scroll_up();
}

void terminal_putchar(char c)
{
	if(c == '\n')
		terminal_new_line();
	else
	{
		terminal_put_entry_at(c, terminal.colour, terminal.column, terminal.row);
		++terminal.column;
		if(terminal.column == VGA_WIDTH)
			terminal_new_line();
	}
	if(!terminal.writing)
		terminal_move_cursor(terminal.column, terminal.row);
}

void terminal_putstring(const char *str)
{
	while(*str != '\0')
		terminal_putchar(*(str++));
}

void terminal_scroll_up(void)
{
	memcpy(terminal.buffer, &terminal.buffer[VGA_COORD_TO_IDX(0, 1)],
	       (VGA_WIDTH*(VGA_HEIGHT-1))*sizeof(VGA_entry_t));
	memsetw(&terminal.buffer[VGA_COORD_TO_IDX(0, VGA_HEIGHT-1)], empty_cell, VGA_WIDTH);
}

void terminal_clear_screen(void)
{
	memsetw(terminal.buffer, empty_cell, VGA_HEIGHT*VGA_WIDTH);
}

/** static functions code **/

static void terminal_move_cursor(int x, int y)
{
	uint16_t location = (y*VGA_WIDTH) + x;

	/* 0x3D4-0x3D5 are in VGA address space */
	outb(0x3D4, 0x0F);
	outb(0x3D5, (BYTE)(location & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (BYTE)((location>>8) & 0xFF));
}


#include "terminal.h"
#include "../memcpy.h"
#include "../memset.h"

void terminal_init(void)
{
	size_t y, x;
	terminal.row = terminal.column = 0;
	terminal.colour = make_VGA_entry(COLOR_LIGHT_GREY, COLOR_WHITE);
	terminal.buffer = (uint16_t *)(VGA_BUFFER_ADDRESS);
	for(y = 0; y < VGA_HEIGHT; ++y)
		for(x = 0; x < VGA_WIDTH; ++x)
			terminal.buffer[VGA_COORD_TO_IDX(x, y)] = make_VGA_entry(' ', terminal.colour);
}

void terminal_set_colour(colour_t colour)
{
	terminal.colour = colour;
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
		terminal_scroll_down();
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
}

void terminal_putstring(const char *str)
{
	while(*str != '\0')
		terminal_putchar(*(str++));
}

void terminal_scroll_down(void)
{
	int i;
	memcpy(terminal.buffer, &terminal.buffer[VGA_COORD_TO_IDX(0, 1)], (VGA_WIDTH*(VGA_HEIGHT-1))*sizeof(uint16_t));

	for(i = 0; i < VGA_WIDTH; ++i)
		terminal_put_entry_at(' ', terminal.colour, i, VGA_HEIGHT-1);
}


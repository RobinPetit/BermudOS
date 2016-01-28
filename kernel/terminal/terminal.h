#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdbool.h>
#include "../video/VGA_management.h"

struct terminal_s
{
	size_t row;        /* Y coordinate */
	size_t column;     /* X coordinate */
	colour_t colour;   /* Colour of the cell */
	VGA_entry_t* buffer;  /* address of the buffer to write the data in */
	bool writing;

};

extern struct terminal_s terminal;

void terminal_init(void);
void terminal_set_colour(colour_t);
void terminal_put_entry_at(char, colour_t, size_t, size_t);
void terminal_new_line(void);
void terminal_putchar(char);
void terminal_putstring(const char *);
void terminal_scroll_up(void);
void terminal_clear_screen(void);

#endif /* TERMINAL_H */

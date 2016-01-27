#if defined (__cplusplus)
 #error "Must be compiled as C code!"
#endif
#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

/* Only compiler-specific headers can be included */
#include <stddef.h>   /* casual types */
#include <stdint.h>   /* defined size integer types */
#include <stdbool.h>  /* boolean type */

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER_ADDRESS 0xB8000 /* defined location on the VGA buffer */
#define VGA_COORD_TO_IDX(x, y) ((y)*VGA_WIDTH + (x))

typedef uint8_t colour_t;

/* VGA Hardware interface */
enum VGA_Colour
{
	COLOR_BLACK = 0,
	COLOR_BLUE,
	COLOR_GREEN,
	COLOR_CYAN,
	COLOR_RED,
	COLOR_MAGENTA,
	COLOR_BROW,
	COLOR_LIGHT_GREY,
	COLOR_DARK_GREY,
	COLOR_LIGHT_BLUE,
	COLOR_LIGHT_GREEN,
	COLOR_LIGHT_CYAN,
	COLOR_LIGHT_RED,
	COLOR_LIGHT_MAGENTA,
	COLOR_LIGHT_BROWN,
	COLOR_WHITE = 15
};

static struct
{
	size_t row;        /* Y coordinate */
	size_t column;     /* X coordinate */
	colour_t colour;   /* Colour of the cell */
	uint16_t* buffer;  /* address of the buffer to write the data in */

} terminal;

colour_t make_colour(enum VGA_Colour foreground, enum VGA_Colour background)
{
	return foreground | (background << 4);
}

uint16_t make_VGA_entry(char c, colour_t colour)
{
	return (uint16_t)(c) | ((uint16_t)(colour) << 8);
}

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

void terminal_putchar(char c)
{
	terminal_put_entry_at(c, terminal.colour, terminal.column, terminal.row);
	++terminal.column;
	if(terminal.column == VGA_WIDTH)
	{
		terminal.column = 0;
		++terminal.row;
		if(terminal.row == VGA_HEIGHT)
			terminal.row = 0;
	}
}

void terminal_putstring(const char *str)
{
	while(*str != '\0')
	{
		terminal_putchar(*(str++));
	}
}

void kernel_main(void)
{
	terminal_init();
	terminal_putstring("Hello World!");
}


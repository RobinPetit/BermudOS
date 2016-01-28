#ifndef VGA_MANAGEMENT_H
#define VGA_MANAGEMENT_H

#include <stdint.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_BUFFER_ADDRESS 0xB8000 /* defined location on the VGA buffer */
#define VGA_COORD_TO_IDX(x, y) ((y)*VGA_WIDTH + (x))

typedef uint8_t colour_t;
typedef uint16_t VGA_entry_t;

/* VGA Hardware interface */
enum VGA_Colour
{
	COLOUR_BLACK = 0,
	COLOUR_BLUE,
	COLOUR_GREEN,
	COLOUR_CYAN,
	COLOUR_RED,
	COLOUR_MAGENTA,
	COLOUR_BROW,
	COLOUR_LIGHT_GREY,
	COLOUR_DARK_GREY,
	COLOUR_LIGHT_BLUE,
	COLOUR_LIGHT_GREEN,
	COLOUR_LIGHT_CYAN,
	COLOUR_LIGHT_RED,
	COLOUR_LIGHT_MAGENTA,
	COLOUR_LIGHT_BROWN,
	COLOUR_WHITE = 15
};

colour_t make_colour(enum VGA_Colour, enum VGA_Colour);
VGA_entry_t make_VGA_entry(char, colour_t);

#endif /* VGA_MANAGEMENT_H */

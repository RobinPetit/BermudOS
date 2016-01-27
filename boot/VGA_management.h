#ifndef VGA_MANAGEMENT_H
#define VGA_MANAGEMENT_H

#include <stdint.h>

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

colour_t make_colour(enum VGA_Colour, enum VGA_Colour);
uint16_t make_VGA_entry(char, colour_t);

#endif /* VGA_MANAGEMENT_H */

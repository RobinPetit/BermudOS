#include "VGA_management.h"

colour_t make_colour(enum VGA_Colour foreground, enum VGA_Colour background)
{
	return foreground | (background << 4);
}

uint16_t make_VGA_entry(char c, colour_t colour)
{
	return (uint16_t)(c) | ((uint16_t)(colour) << 8);
}


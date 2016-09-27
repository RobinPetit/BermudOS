#ifndef KEYBOARD_H
#define KEYBOARD_H

#define PS2_DATA_REGISTER 0x60
#define PS2_COMMAND_REGISTER 0x64

#define KEYBOARD_SIZE 0x80
#define KEYBOARD_BUFFER_SIZE 0x400

#define NO_RETURN (KEYBOARD_BUFFER_SIZE + 1)

#include <mem/_memtypes.h>
#include <stdbool.h>

typedef BYTE scancode_t;

int keyboard_setup(void);
void read_keyboard_buffer(char *destination);

struct keyboard_buffer
{
	BYTE buffer[KEYBOARD_BUFFER_SIZE+1];
	uint16_t index;
	BYTE overflow;
	uint16_t first_return;
	uint16_t start_index;
};

struct keyboard_state
{
	BYTE pressed_keys[KEYBOARD_SIZE / 8];
	struct keyboard_buffer buffer;
	struct
	{
		bool caps_lock:1;
		bool num_lock:1;
	} special_keys;
	bool enable_printing;
};

#endif

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define PS2_DATA_REGISTER 0x60
#define PS2_COMMAND_REGISTER 0x64

#define KEYBOARD_SIZE 0x80

int keyboard_setup(void);

#endif

#include "keyboard.h"
#include "../interrupts/IRQ/irq.h"
#include "../../io/in.h"
#include <string.h>

/* static prototypes */
static void keyboard_handler(struct interrupt_stack_state *);

enum keyboard_scancodes
{
	SCANCODE_NONE=0,
	SCANCODE_ESCAPE,
	SCANCODE_ONE,
	SCANCODE_AMPERSTAND=SCANCODE_ONE,
	SCANCODE_TWO,
	SCANCODE_THREE,
	SCANCODE_QUOTE_MARK=SCANCODE_THREE,
	SCANCODE_OCTOTHORP=SCANCODE_THREE,
	SCANCODE_FOUR,
	SCANCODE_APOSTROPHE=SCANCODE_FOUR,
	SCANCODE_FIVE,
	SCANCODE_OPEN_BRACKET=SCANCODE_FIVE,
	SCANCODE_SIX,
	SCANCODE_PARAGRAPH=SCANCODE_SIX,
	SCANCODE_SEVEN,
	SCANCODE_EIGHT,
	SCANCODE_EXCLAMATION_MARK=SCANCODE_EIGHT,
	SCANCODE_NINE,
	SCANCODE_LEFT_CURLY_BRACKET=SCANCODE_NINE,
	SCANCODE_ZERO,
	SCANCODE_RIGHT_CURLY_BRACKET=SCANCODE_ZERO,
	SCANCODE_DEGREE_SYMBOL,
	SCANCODE_RIGHT_BRACKET=SCANCODE_DEGREE_SYMBOL,
	SCANCODE_HYPHEN,
	SCANCODE_BACKSPACE,
	SCANCODE_TAB,
	SCANCODE_A,
	SCANCODE_Z,
	SCANCODE_E,
	SCANCODE_R,
	SCANCODE_T,
	SCANCODE_Y,
	SCANCODE_U,
	SCANCODE_I,
	SCANCODE_O,
	SCANCODE_P,
	SCANCODE_LEFT_SQUARE_BRACKET,
	SCANCODE_RIGHT_SQUARE_BRACKET,
	SCANCODE_DOLLAR_SIGN=SCANCODE_RIGHT_SQUARE_BRACKET,
	SCANCODE_STAR=SCANCODE_RIGHT_SQUARE_BRACKET,
	SCANCODE_ENTER,
	SCANCODE_CTRL,
	SCANCODE_Q,
	SCANCODE_S,
	SCANCODE_D,
	SCANCODE_F,
	SCANCODE_G,
	SCANCODE_H,
	SCANCODE_J,
	SCANCODE_K,
	SCANCODE_L,
	SCANCODE_M,
	SCANCODE_PERCENT,
	SCANCODE_EXPOSANT_TWO,
	SCANCODE_LEFT_SHIFT,
	SCANCODE_GRAVE_ACCENT,
	SCANCODE_W,
	SCANCODE_X,
	SCANCODE_C,
	SCANCODE_V,
	SCANCODE_B,
	SCANCODE_N,
	SCANCODE_COMMA,
	SCANCODE_QUESTION_MARK=SCANCODE_COMMA,
	SCANCODE_SEMICOLON,
	SCANCODE_DOT=SCANCODE_SEMICOLON,
	SCANCODE_COLON,
	SCANCODE_SLASH=SCANCODE_COLON,
	SCANCODE_EQUAL_SIGN,
	SCANCODE_PLUS_SIGN=SCANCODE_EQUAL_SIGN,
	SCANCODE_RIGHT_SHIFT,
	SCANCODE_NUMPAD_STAR,
	SCANCODE_ALT,
	SCANCODE_WHITESPACE,
	SCANCODE_CAPS_LOCK,
	SCANCODE_F1,
	SCANCODE_F2,
	SCANCODE_F3,
	SCANCODE_F4,
	SCANCODE_F5,
	SCANCODE_F6,
	SCANCODE_F7,
	SCANCODE_F8,
	SCANCODE_F9,
	SCANCODE_F10,
	SCANCODE_NUM_LOCK,
	SCANCODE_UNKNOWN_70,
	SCANCODE_NUMPAD_SEVEN,
	SCANCODE_NUMPAD_EIGHT,
	SCANCODE_NUMPAD_NINE,
	SCANCODE_NUMPAD_MINUS,
	SCANCODE_NUMPAD_FOUR,
	SCANCODE_NUMPAD_FIVE,
	SCANCODE_NUMPAD_SIX,
	SCANCODE_NUMPAD_PLUS,
	SCANCODE_NUMPAD_ONE,
	SCANCODE_NUMPAD_TWO,
	SCANCODE_NUMPAD_THREE,
	SCANCODE_NUMPAD_ZERO,
	SCANCODE_NUMPAD_DOT,
	SCANCODE_UNKNOWN_84,
	SCANCODE_UNKNOWN_85,
	SCANCODE_LESS,
	SCANCODE_GREATER=SCANCODE_LESS,
	SCANCODE_F11,
	SCANCODE_F12,
	SCANCODE_UNKNOWN_89,
	SCANCODE_UNKNOWN_90,
	SCANCODE_WINDOWS_KEY,
	SCANCODE_UNKNOWN_92,
	SCANCODE_RIGHT_CLICK_MENU,
	SCANCODE_UNKNOWN
};

static const char scancodes[KEYBOARD_SIZE] = 
{
	0,	/* None */
	0,	/* Esc */
	'&',
	0,	/* é */
	'"',
	'\'',
	'(',
	0,	/* § */
	0,	/* è */
	'!',
	0,	/* ç */
	0,	/* à */
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
	0,	/* ù */
	0,	/* ² */
	0,	/* Left Shift */
	0,	/* µ */
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
	0,	/* UNKNOWN YET: 70 */
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

static const char maj_scancodes[KEYBOARD_SIZE] =
{
	0,
	0,
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
	0,	/* ° */
	'_',
	0,	/* Back */
	0,	/* Tab */
	'A',
	'Z',
	'E',
	'r',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	0,	/* ^ */
	'*',
	'\n',	/* Enter */
	0,	/*Ctrl*/
	'Q',
	'S',
	'D',
	'F',
	'G',
	'H',
	'J',
	'K',
	'L',
	'M',
	'%',
	0,	/* ³ */
	0,	/* Left Shift */
	0,	/* £ */
	'W',
	'X',
	'C',
	'V',
	'B',
	'N',
	'?',
	'.',
	'/',
	'+',
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
	0,	/* UNKNOWN YET: 70 */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* NumPad */
	0,	/* UNKNOWN YET: 84 */
	0,	/* UNKNOWN YET: 85 */
	'>',
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

volatile struct keyboard_state kb_state = {{}, {{}, 0, 0, NO_RETURN, 0}, {0, 0}, true};

int keyboard_setup(void)
{
	return set_irq(1, keyboard_handler);
}

static inline int is_release_signal(scancode_t scancode)
{
	return scancode & 0x80;
}

static inline int is_press_signal(scancode_t scancode)
{
	return !is_release_signal(scancode);
}

static inline unsigned int keyboard_code_to_idx(enum keyboard_scancodes code)
{
	return code / 8;
}

static inline unsigned int keyboard_code_to_offset(enum keyboard_scancodes code)
{
	return code % 8;
}

static bool keyboard_is_pressed(enum keyboard_scancodes code)
{
	return kb_state.pressed_keys[keyboard_code_to_idx(code)] & (1 << keyboard_code_to_offset(code));
}

static void keyboard_handler(struct interrupt_stack_state *registers)
{
	(void)(registers);  /* signal that register parameter is not used */
	uint16_t idx = kb_state.buffer.index;
	/* have the variable static to not be removed each time the function ends: values MUST be kept */
	scancode_t input_scancode = inb(PS2_DATA_REGISTER);
	if(is_release_signal(input_scancode))
		kb_state.pressed_keys[(input_scancode & 0X7f) / 8] &= (BYTE)(~(1 << ((input_scancode & 0x7F) % 8)));
	else
	{
		kb_state.pressed_keys[input_scancode / 8] |= (1 << (input_scancode % 8));
		if(kb_state.buffer.index < KEYBOARD_BUFFER_SIZE)
		{
			if(input_scancode == SCANCODE_CAPS_LOCK)
				kb_state.special_keys.caps_lock = 1 - kb_state.special_keys.caps_lock;
			else if(input_scancode == SCANCODE_NUM_LOCK)
				kb_state.special_keys.num_lock = 1 - kb_state.special_keys.num_lock;
			/* Make an XOR between shift and CAPS LOCK to know if secundary keys */
			else if((keyboard_is_pressed(SCANCODE_LEFT_SHIFT) || keyboard_is_pressed(SCANCODE_RIGHT_SHIFT)) ^ kb_state.special_keys.caps_lock)
			{
				if(maj_scancodes[input_scancode] != 0)
					kb_state.buffer.buffer[kb_state.buffer.index++] = maj_scancodes[input_scancode];
			}
			else
			{
				if(scancodes[input_scancode] != 0)
					kb_state.buffer.buffer[kb_state.buffer.index++] = scancodes[input_scancode];
			}
		}
		else
			kb_state.buffer.overflow = true;
	}
	if(idx != kb_state.buffer.index)
	{
		if(kb_state.enable_printing)
			putchar(kb_state.buffer.buffer[idx]);
		if(kb_state.buffer.buffer[idx] == '\n' && kb_state.buffer.first_return == NO_RETURN)
			kb_state.buffer.first_return = idx;
	}
}

void read_keyboard_buffer(char *destination)
{
	/* Amelioration to keep in mind: use the buffer as circular to not be bothered by the changing value of buffer::start_index */
	while(kb_state.buffer.first_return == NO_RETURN && !kb_state.buffer.overflow)
		;
	if(kb_state.buffer.first_return != NO_RETURN)
	{
		char *ptr = strchr(&kb_state.buffer.buffer[kb_state.buffer.first_return+1], '\n');
		strncpy(destination, &kb_state.buffer.buffer[kb_state.buffer.start_index], kb_state.buffer.first_return+1-kb_state.buffer.start_index);
		destination[kb_state.buffer.first_return+1-kb_state.buffer.start_index] = '\0';
		kb_state.buffer.start_index = kb_state.buffer.first_return+1;
		kb_state.buffer.first_return = (ptr == NULL) ? NO_RETURN : (uint16_t)((void *)ptr - (void *)(kb_state.buffer.buffer));
		if(kb_state.buffer.first_return == NO_RETURN && kb_state.buffer.index <= kb_state.buffer.start_index)
			kb_state.buffer.index = kb_state.buffer.start_index = 0;
	}
	else
	{
		size_t end_pos = (kb_state.buffer.first_return == NO_RETURN) ? KEYBOARD_BUFFER_SIZE : kb_state.buffer.first_return;
		strncpy(destination, &kb_state.buffer.buffer[kb_state.buffer.start_index], end_pos - kb_state.buffer.start_index);
		destination[end_pos - kb_state.buffer.start_index] = '\0';
		if(kb_state.buffer.first_return != NO_RETURN)
		{
			memmove(kb_state.buffer.buffer, &kb_state.buffer.buffer[kb_state.buffer.first_return+1], KEYBOARD_BUFFER_SIZE-kb_state.buffer.first_return-1);
			kb_state.buffer.start_index = 0;
			kb_state.buffer.index = KEYBOARD_BUFFER_SIZE-kb_state.buffer.first_return+1;
			char *ptr = strchr(kb_state.buffer.buffer, '\n');
			kb_state.buffer.first_return = (ptr == NULL) ? NO_RETURN : (uint16_t)((void *)ptr - (void *)(kb_state.buffer.buffer));
		}
		else
			kb_state.buffer.index = kb_state.buffer.start_index = 0;
		kb_state.buffer.overflow = false;
	}
}


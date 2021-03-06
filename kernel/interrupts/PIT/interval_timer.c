#include "interval_timer.h"
#include "../idt.h"
#include "../IRQ/irq.h"
#include "../../io/out.h"

#define PIT_LOW_BYTE 0x01
#define PIT_HIGH_BYTE 0x02
#define PIT_LOW_HIGH_BYTE 0x03

enum PIT_mode_e
{
	ON_TERMINAL=0x00,
	HARDWARE_ONE_SHOT=0x01,
	RATE_GENERATOR=0x02,
	SQUARE_WAVE=0x03,
	SOFTWARE_STROBE=0x04,
	HARDWARE_STROBE=0x05,
	OUT_OF_RANGE=0x08
};

#define PIT_16_BITS_BINARY_VALUE 0x00
#define PIT_4_DIGITS_BCR 0x01

#define PIT_MAKE_BYTE(counter, data_info, mode, bit_counter) \
	(BYTE)(((counter & 0x03) << 6) | ((data_info & 0x03) << 4) | ((mode & 0x07) << 1) | (bit_counter & 0x01))

static uint32_t tick_frequency = PIT_DEFAULT_FREQUENCY;
static volatile uint32_t PIT_current_tick = 0;  /* declare it volatile since it is modified inside the related irq manager */

void timer_handler(struct interrupt_stack_state *);
static void set_timer_divisor(uint16_t);

bool timer_setup(void)
{
	set_timer_divisor(0xFFFF);
	return set_irq(0, timer_handler);
}

void PIT_set_frequency_i(uint32_t new_frequency)
{
	tick_frequency = new_frequency;
	set_timer_divisor(PIT_ABSOLUTE_TICK / new_frequency);
}

void PIT_set_frequency_f(float new_frequency)
{
	tick_frequency = (uint32_t)new_frequency;
	set_timer_divisor(PIT_ABSOLUTE_TICK / new_frequency);
}

static void set_timer_divisor(uint16_t divisor)
{
	/* precise 2 bytes are given on channel 0:
	 * first low byte then high byte*/
	outb(PIT_COMMAND, PIT_MAKE_BYTE(0, PIT_LOW_HIGH_BYTE, SQUARE_WAVE, PIT_16_BITS_BINARY_VALUE));
	outb(PIT_DATA_CHANNEL_0, divisor & 0xFF);  /* low byte */
	outb(PIT_DATA_CHANNEL_0, (divisor >> 8) & 0xFF);
}

void timer_handler(struct interrupt_stack_state *registers)
{
	++PIT_current_tick;
}

uint32_t get_current_PIT_tick(void)
{
	return PIT_current_tick;
}

uint32_t seconds_to_ticks(uint32_t sec)
{
	return sec * tick_frequency;
}


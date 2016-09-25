#ifndef PROGRAMMABLE_INTERVAL_TIMER_H
#define PROGRAMMABLE_INTERVAL_TIMER_H

#include <stdbool.h>
#include <stdint.h>

#define PIT_ABSOLUTE_TICK 0x001234DC
#define PIT_DEFAULT_FREQUENCY 18 /* Hz with divisor = 65535 */

#define PIT_DATA_CHANNEL_0 0x40
#define PIT_DATA_CHANNEL_1 0x41
#define PIT_DATA_CHANNEL_2 0x42
#define PIT_COMMAND 0x43

bool timer_setup(void);
void PIT_set_frequency_i(uint32_t);
void PIT_set_frequency_f(float);

uint32_t get_current_PIT_tick(void);
uint32_t seconds_to_ticks(uint32_t);

#endif /* PROGRAMMABLE_INTERVAL_TIMER_H */

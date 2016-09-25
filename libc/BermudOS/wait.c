#include <BermudOS/wait.h>
#include "../../kernel/interrupts/PIT/interval_timer.h"

void wait_ticks(uint32_t ticks)
{
	uint32_t end = get_current_PIT_tick() + ticks;
	while(get_current_PIT_tick() < end)
		;
}

void wait_msec(uint32_t msec)
{
	wait_ticks(seconds_to_ticks(msec) / 1000);
}

void wait_sec(uint32_t sec)
{
	wait_ticks(seconds_to_ticks(sec));
}

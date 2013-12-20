/*
 * Copyright (C) 2013 Christian Mehlis <christian.mehlis@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "hwtimer.h"
#include "ltc4150.h"
#include "thread.h"

uint32_t tick_ticks = HWTIMER_TICKS(500 * 1000);
int hwtimer_tick_id;

void test_ltc_tick(void *ptr)
{
    int pid = (int) ptr;

    hwtimer_tick_id = hwtimer_set(tick_ticks, test_ltc_tick, ptr);
    thread_wakeup(pid);
}

int main(void)
{
    ltc4150_start();

    hwtimer_tick_id = hwtimer_set(tick_ticks,
                                  test_ltc_tick,
                                  (void *) thread_pid);

    while (1) {
        thread_sleep();
        printf("Power usage: %.4f mA (%.4f mA avg/ %.4f mAh total / %i usec)\n",
                ltc4150_get_current_mA(), ltc4150_get_avg_mA(),
                ltc4150_get_total_mAh(), ltc4150_get_interval());
    }

    return 0;
}

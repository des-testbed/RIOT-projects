/*
 * Copyright (C) 2008, 2009, 2010  Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 Christian Mehlis <christian.mehlis@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>

#include "hwtimer.h"
#include "thread.h"

#include "swtimer.h"

int main(void)
{
    hwtimer_init();
    swtimer_init();

    puts("Hello world!\n");

    swtimer_t t;

    puts("Setting timer...\n");
    swtimer_set_wakeup(&t, 10000000L, thread_pid);
    puts("Small delay...\n");
    hwtimer_wait(200000);
    puts("Removing timer...\n");
    swtimer_remove(&t);
    puts("Done.\n");

    swtimer_t t2;
    puts("Setting timer...\n");
    swtimer_set_wakeup(&t, 10000000L, thread_pid);
    puts("Setting timer 2...\n");
    swtimer_set_wakeup(&t2, 50000000L, thread_pid);
    puts("Small delay...\n");
    hwtimer_wait(200000);
    puts("Removing timer 1...\n");
    swtimer_remove(&t);
    puts("Removing timer 2...\n");
    swtimer_remove(&t2);
    puts("Done.\n");

    puts("Setting timer...\n");
    swtimer_set_wakeup(&t, 10000000L, thread_pid);
    puts("Setting timer 2...\n");
    swtimer_set_wakeup(&t2, 50000000L, thread_pid);
    puts("Small delay...\n");
    hwtimer_wait(200000);
    puts("Removing timer 2...\n");
    swtimer_remove(&t2);
    puts("Removing timer 1...\n");
    swtimer_remove(&t);
    puts("Done.\n");
}

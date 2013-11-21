/*
 * Copyright (C) 2008, 2009, 2010  Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 Christian Mehlis <christian.mehlis@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>
#include <inttypes.h>

#include "hwtimer.h"
#include "swtimer.h"
#include "thread.h"
#include "msg.h"

static char thread1_stack[KERNEL_CONF_STACKSIZE_PRINTF];
static char thread2_stack[KERNEL_CONF_STACKSIZE_PRINTF];

void wakeup_thread(void)
{
    puts("wakeup");
}

void msg_thread(void)
{
    msg_t m;
    msg_receive(&m);
    printf("'%s' - pid=%" PRIu16 " - type=%" PRIu16 "\n", (char*) m.content.ptr, m.sender_pid, m.type);
}

int main(void)
{
    hwtimer_init();
    swtimer_init();

    int pid1 = thread_create(thread1_stack, KERNEL_CONF_STACKSIZE_PRINTF,
            PRIORITY_MAIN - 1,
            CREATE_WOUT_YIELD | CREATE_SLEEPING | CREATE_STACKTEST,
            wakeup_thread, "nr1");

    int pid2 = thread_create(thread2_stack, KERNEL_CONF_STACKSIZE_PRINTF,
            PRIORITY_MAIN - 1,
            /*CREATE_WOUT_YIELD | CREATE_SLEEPING |*/CREATE_STACKTEST,
            msg_thread, "nr2");

    swtimer_t wut;
    swtimer_t mst;

    /* test wake-up */
    swtimer_set_wakeup(&wut, 1000L, pid1);
    /* test message */
    swtimer_set_msg(&mst, 1000L, pid2, "message text 123");

    puts("DONE");
}

#include <stdio.h>

#include "hwtimer.h"

void callback(void* ptr)
{
    puts((char*) ptr);
}

int main(void)
{
    puts("hwtimer test project...");

    puts("Initializing hwtimer...");
    hwtimer_init();

    puts("Initializing hwtimer [OK].");

#define BASE_DELAY 100000UL
#define DELTA_DELAY 10000UL
#define MSGLEN 12 // == strlen("callback %2i")
    char msg[MSGLEN * ARCH_MAXTIMERS]; // == [callback  1\0callback  2\0...]
    unsigned long delay = BASE_DELAY + (ARCH_MAXTIMERS * DELTA_DELAY);
    /* set up to ARCH_MAXTIMERS-1 because hwtimer_wait below also
     * needs a timer */
    for (int i = 0; i < (ARCH_MAXTIMERS - 1); i++) {
        char *msgn = msg + (i*MSGLEN);
        delay -= DELTA_DELAY;
        snprintf(msgn, MSGLEN, "callback %2x", i+1);
        hwtimer_set(delay, callback, (void*) msgn);
        printf("set %s\n", msgn);
    }

    hwtimer_wait(HWTIMER_TICKS(1000UL * 1000UL));

    puts("hwtimer set.");
}

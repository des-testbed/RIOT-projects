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

    hwtimer_set(20000LU, callback, (void*) "callback1");
    hwtimer_set(50000LU, callback, (void*) "callback2");
    hwtimer_set(30000LU, callback, (void*) "callback3");

    hwtimer_wait(HWTIMER_TICKS(1000UL * 1000UL));

    puts("hwtimer set.");
}

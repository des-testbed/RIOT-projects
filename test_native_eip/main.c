/*
 * Copyright (C) 2013 Ludwig Ortmann <ludwig.ortmann@fu-berlin.de>
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#include "hwtimer.h"
#include "thread.h"

char t1_stack[KERNEL_CONF_STACKSIZE_PRINTF];
char t2_stack[KERNEL_CONF_STACKSIZE_PRINTF];
extern int printf(const char *format, ...);

char c;

void t1(void)
{
    int j = 0;

    while(1) {
        j++;
        c = (j%20)+60; 
    }
}

void t2(void)
{
    char oldx = 0;
    while(1) {
        char x = c;
        x++;
        if (x != oldx) {
            putchar(x);
            oldx = x;
        }
    }
}


int main(void)
{
    thread_create(
            t1_stack,
            KERNEL_CONF_STACKSIZE_PRINTF,
            PRIORITY_MAIN+2,
            0,
            t1,
            "t1"
            );
    printf("t1 created\n");
    thread_create(
            t2_stack,
            KERNEL_CONF_STACKSIZE_PRINTF,
            PRIORITY_MAIN+2,
            0,
            t2,
            "t2"
            );
    printf("t2 created\n");

    printf("hwtimer_wait()\n");
    for (int j = 0; j < 20; j++) {
        for (unsigned long i = 65536; i; i = i>>1) {
            //printf("sleep %lu\n", i);
            hwtimer_wait(i);
        }
    }


    exit(0);
    printf("main: shutdown\n");
    extern void shutdown(void);
    shutdown();
}

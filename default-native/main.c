/*
 * Copyright (C) 2013 Ludwig Ortmann <ludwig.ortmann@fu-berlin.de>
 */

#include <stdio.h>
#include <time.h>

#include <vtimer.h>
#include <rtc.h>
//#include <board_uart0.h>
#include <shell.h>
#include <shell_commands.h>


int main(void)
{
    struct tm localt;
    shell_t shell;

    printf("\n\t\t\tWelcome to RIOT\n\n");

    rtc_get_localtime(&localt);
    printf("The time is now: %s\n", asctime(&localt));

    printf("Hold on a second...\n");
    vtimer_usleep(1000000);
    printf("You may use the shell now.\n");

    shell_init(&shell, NULL, getchar, putchar);
    shell_run(&shell);
        
    return 0;
}

/*
 * Copyright (C) 2013 Ludwig Ortmann <ludwig.ortmann@fu-berlin.de>
 */

#include <stdio.h>
#include <time.h>

#include <vtimer.h>
#include <rtc.h>
#include <board_uart0.h>
#include <shell.h>
#include <shell_commands.h>
#include <board.h>
#include <cc110x_ng.h>
#include <transceiver.h>
#include <posix_io.h>

int main(void)
{
    struct tm localt;
    shell_t shell;

    printf("\n\tmain(): initializing transceiver\n");
    transceiver_init(TRANSCEIVER_CC1100);
    printf("\n\tmain(): starting transceiver\n");
    transceiver_start();
    board_uart0_init();
    posix_open(uart0_handler_pid, 0);

    printf("\n\t\t\tWelcome to RIOT\n\n");

    rtc_get_localtime(&localt);
    printf("The time is now: %s\n", asctime(&localt));

    /* fancy greeting */
    printf("Hold on half a second...\n");
    LED_RED_TOGGLE();
    vtimer_usleep(500000);
    LED_RED_TOGGLE();
    LED_GREEN_ON();
    LED_GREEN_OFF();

    printf("You may use the shell now.\n");
    printf("Type help for help, ctrl+c to exit.\n");

    shell_init(&shell, NULL, uart0_readc, uart0_putc);
    shell_run(&shell);
        
    return 0;
}

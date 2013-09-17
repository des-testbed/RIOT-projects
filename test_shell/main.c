/*
 * main.c - Main function of the test_shell project.
 * Copyright (C) 2013 Kaspar Schleiser <kaspar@schleiser.de>
 *
 * This source code is licensed under the LGPLv2 license,
 * See the file LICENSE for more details.
 *
 */

/**
 * @file
 * @internal
 * @brief       shows how to set up own and use the system shell commands.
 *              By typing help in the serial console, all the supported commands
 *              are listed.
 *
 * @author      Freie Universität Berlin, Computer Systems & Telematics
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version     $Revision: 3855 $
 *
 * @note        $Id: main.c 3855 2013-09-04 17:00:33 kasmi $
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <shell_commands.h>
#include <posix_io.h>
#include <shell.h>
#include <board_uart0.h>

void print_teststart(char *str)
{
    printf("[TEST_START]\n");

}

void print_testend(char *str)
{
    printf("[TEST_END]\n");
}

void print_own_test(char *str)
{
    printf("[OWN_TEST]\n");
    printf("[OWN_TEST]: input = %s\n", str);
}

int shell_readc(void)
{
    char c = 0;
    posix_read(uart0_handler_pid, &c, 1);
    return c;
}

void shell_putchar(int c)
{
    putchar(c);
}

const shell_command_t shell_commands[] = {
    { "start_test", "starts a test", print_teststart },
    { "end_test", "ends a test", print_testend },
    { "start_own_test", "starts own test", print_own_test },
    { NULL, NULL, NULL }
};

int main(void)
{

    printf("test_shell.\n");

    board_uart0_init();

    posix_open(uart0_handler_pid, 0);

    //define own shell
    shell_t shell;
    shell_init(&shell, shell_commands, shell_readc, shell_putchar);
    shell_run(&shell);

    //init system shell
    //shell_t sys_shell;
    //shell_init(&sys_shell, NULL, shell_readc, shell_putchar);
    //shell_run(&sys_shell);

    return 0;
}


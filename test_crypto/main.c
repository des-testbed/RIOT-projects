/*
 * Copyright (C) 2013 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @file        main.c
 * @brief       Application for testing the crypto module
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#include <stdio.h>
#include <string.h>

#include <posix_io.h>
#include <board_uart0.h>
#include <shell.h>
#include <shell_commands.h>

#include "crypto/3des.h"
#include "crypto/aes.h"
#include "crypto/rc5.h"
#include "crypto/skipjack.h"
#include "crypto/twofish.h"
#include "crypto/sha256.h"


static int shell_readc(void) {
    char c = 0;
    (void) posix_read(uart0_handler_pid, &c, 1);
    return c;
}

static void shell_putchar(int c) {
    (void) putchar(c);
}

int main(void) {
    shell_t shell;
    uint8_t block_size;

    (void) posix_open(uart0_handler_pid, 0);
 
    (void) puts("Welcome to RIOT!");
    (void) puts("Playing with some crypto stuff");
    
    uint8_t size = tripledes_get_preferred_block_size();
    printf("3des:     Preferred block size: %i\n", size);
    
    size = aes_get_preferred_block_size();
    printf("aes:      Preferred block size: %i\n", size);
    
    size = rc5_get_preferred_block_size();
    printf("rc5:      Preferred block size: %i\n", size);

//    uint8_t size = shatwofish_get_preferred_block_size();
//    printf("sha256:   Preferred block size: %i\n", size);

    size = skipjack_get_preferred_block_size();
    printf("skipjack: Preferred block size: %i\n", size);
    
    size = twofish_get_preferred_block_size();
    printf("twofish:  Preferred block size: %i\n", size);


    shell_init(&shell, NULL, shell_readc, shell_putchar);
    shell_run(&shell);
    return 0;
}



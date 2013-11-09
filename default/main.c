/*
 * Copyright (C) 2008, 2009, 2010  Kaspar Schleiser <kaspar@schleiser.de>
 * Copyright (C) 2013 Ludwig Ortmann <ludwig.ortmann@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "posix_io.h"
#include "shell.h"
#include "shell_commands.h"
#include "board_uart0.h"

#ifdef MODULE_LTC4150
#include <ltc4150.h>
#endif

#ifdef MODULE_TRANSCEIVER
#include <transceiver.h>
#endif

#define SND_BUFFER_SIZE     (100)
#define RCV_BUFFER_SIZE     (64)
#define RADIO_STACK_SIZE    (KERNEL_CONF_STACKSIZE_DEFAULT)

#ifdef MODULE_TRANSCEIVER
char radio_stack_buffer[RADIO_STACK_SIZE];
msg_t msg_q[RCV_BUFFER_SIZE];

void radio(void) {
    msg_t m;
    radio_packet_t *p;
    radio_packet_length_t i;

    msg_init_queue(msg_q, RCV_BUFFER_SIZE);

    while (1) {
        msg_receive(&m);
        if (m.type == PKT_PENDING) {
            p = (radio_packet_t*) m.content.ptr;
            printf("Got radio packet:\n");
            printf("\tLength:\t%u\n", p->length);
            printf("\tSrc:\t%u\n", p->src);
            printf("\tDst:\t%u\n", p->dst);
            printf("\tLQI:\t%u\n", p->lqi);
            printf("\tRSSI:\t%u\n", p->rssi);

            for (i = 0; i < p->length; i++) {
                printf("%02X ", p->data[i]);
            }
            p->processing--;
            puts("\n");
        }
        else if (m.type == ENOBUFFER) {
            puts("Transceiver buffer full");
        }
        else {
            puts("Unknown packet received");
        }
    }
}
#endif /* MODULE_TRANSCEIVER */

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
    (void) posix_open(uart0_handler_pid, 0);

#ifdef MODULE_LTC4150
    ltc4150_start();
#endif

#ifdef MODULE_TRANSCEIVER
    int radio_pid;
#ifdef MODULE_CC110X
    transceiver_init(TRANSCEIVER_CC1100);
#endif
#ifdef MODULE_CC110X_NG
    transceiver_init(TRANSCEIVER_CC1100);
#endif
#ifdef MODULE_CC2420
    transceiver_init(TRANSCEIVER_CC2420);
#endif
#ifdef MODULE_NATIVENET
    transceiver_init(TRANSCEIVER_NATIVE);
#endif
#ifdef MODULE_AT86RF231
    transceiver_init(TRANSCEIVER_AT86RF231);
#endif
#ifdef MODULE_MC1322X
    transceiver_init(TRANSCEIVER_MC1322X);
#endif
    (void) transceiver_start();
    radio_pid = thread_create(radio_stack_buffer, RADIO_STACK_SIZE, PRIORITY_MAIN-2, CREATE_STACKTEST, radio, "radio");
#ifdef MODULE_CC110X
    transceiver_register(TRANSCEIVER_CC1100, radio_pid);
#endif
#ifdef MODULE_CC110X_NG
    transceiver_register(TRANSCEIVER_CC1100, radio_pid);
#endif
#ifdef MODULE_CC2420
    transceiver_register(TRANSCEIVER_CC2420, radio_pid);
#endif
#ifdef MODULE_NATIVENET
    transceiver_register(TRANSCEIVER_NATIVE, radio_pid);
#endif
#ifdef MODULE_AT86RF231
    transceiver_register(TRANSCEIVER_AT86RF231, radio_pid);
#endif
#ifdef MODULE_MC1322X
    transceiver_register(TRANSCEIVER_MC1322X, radio_pid);
#endif
#endif /* MODULE_TRANSCEIVER */
    
    (void) puts("Welcome to RIOT!");

    shell_init(&shell, NULL, shell_readc, shell_putchar);

    shell_run(&shell);
    return 0;
}

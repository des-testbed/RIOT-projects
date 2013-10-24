/*
 * Copyright (C) 2013 Ludwig Ortmann <ludwig.ortmann@fu-berlin.de>
 */

#include <stdio.h>
#include <time.h>

#include "vtimer.h"
#include "rtc.h"
#include "board_uart0.h"
#include "shell.h"
#include "shell_commands.h"
#include "board.h"
#include "transceiver.h"
#include "posix_io.h"
#include "nativenet.h"
#include "msg.h"
#include <thread.h>

#define SND_BUFFER_SIZE     (100)
#define RCV_BUFFER_SIZE     (64)
#define RADIO_STACK_SIZE    (KERNEL_CONF_STACKSIZE_DEFAULT)

char radio_stack_buffer[RADIO_STACK_SIZE];
msg_t msg_q[RCV_BUFFER_SIZE];

void radio(void) {
    msg_t m;
    radio_packet_t *p;
    uint8_t i;

    msg_init_queue(msg_q, RCV_BUFFER_SIZE);

    while (1) {
        msg_receive(&m);
        if (m.type == PKT_PENDING) {
            p = (radio_packet_t*) m.content.ptr;
            printf("Packet waiting, process %p...\n", p);
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

int main(void)
{
    int radio_pid;
    struct tm localt;
    shell_t shell;

    printf("\n\tmain(): initializing transceiver\n");
    transceiver_init(TRANSCEIVER_NATIVE);

    printf("\n\tmain(): starting transceiver\n");
    transceiver_start();

    printf("\n\tmain(): starting radio thread\n");
    radio_pid = thread_create(radio_stack_buffer, RADIO_STACK_SIZE, PRIORITY_MAIN-2, CREATE_STACKTEST, radio, "radio");
    transceiver_register(TRANSCEIVER_NATIVE, radio_pid);

    posix_open(uart0_handler_pid, 0);


    printf("\n\t\t\tWelcome to RIOT\n\n");

    rtc_get_localtime(&localt);
    printf("The time is now: %s\n", asctime(&localt));

    /* fancy greeting */
    printf("Hold on half a second...\n");
    LED_RED_TOGGLE;
    vtimer_usleep(500000);
    LED_RED_TOGGLE;
    LED_GREEN_ON;
    LED_GREEN_OFF;

    printf("You may use the shell now.\n");
    printf("Type help for help, ctrl+c to exit.\n");

    shell_init(&shell, NULL, uart0_readc, uart0_putc);
    shell_run(&shell);
        
    return 0;
}

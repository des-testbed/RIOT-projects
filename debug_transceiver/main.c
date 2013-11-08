/*
 * Copyright (C) 2013 Ludwig Ortmann <ludwig.ortmann@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <time.h>

#include "hwtimer.h"
#include "board.h"
#include "board_uart0.h"
#include "msg.h"
#include "thread.h"
#include "posix_io.h"
#include "shell.h"
#include "shell_commands.h"
#include "transceiver.h"
#include "radio/types.h"

#define SND_BUFFER_SIZE     (100)
#define RCV_BUFFER_SIZE     (64)
#define RADIO_STACK_SIZE    (KERNEL_CONF_STACKSIZE_PRINTF)

#ifdef MODULE_NATIVENET
#define TRANSCEIVER_TYPE TRANSCEIVER_NATIVE
#endif

char radio_stack_buffer[RADIO_STACK_SIZE];
msg_t msg_q[RCV_BUFFER_SIZE];
uint8_t snd_buffer[NATIVE_MAX_DATA_LENGTH];
int radio_pid;

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

void start_radio()
{
    if(radio_pid == -1) {
        printf("starting radio thread..");
        radio_pid = thread_create(
                radio_stack_buffer,
                RADIO_STACK_SIZE,
                PRIORITY_MAIN-2,
                CREATE_STACKTEST,
                radio,
                "radio");
        transceiver_register(TRANSCEIVER_TYPE, radio_pid);
        printf(" done\n");
    }
    else {
        printf("radio thread already running\n");
    }
}

void stop_radio()
{
    if (radio_pid == -1) {
        printf("radio thread not running");
    }
    else {
        printf("stopping radio thread..");
        printf(" XXX not implemented XXX");
        printf(" done\n");
    }
}

void sc_start_stop_radio(char *str)
{
    if (strcmp(str + 6, "start") == 0) {
        start_radio();
    }
    else if (strcmp(str + 6, "stop") == 0) {
        stop_radio();
    }
    else {
        printf("usage: radio <start|stop>\n");
    }
}

void traffic_gen(int count, int size, radio_address_t addr)
{
    msg_t mesg;
    transceiver_command_t tcmd;
    char text_msg[size];

    radio_packet_t p;
    uint32_t response;

    tcmd.transceivers = TRANSCEIVER_TYPE;
    tcmd.data = &p;
    memset(text_msg, 1, size);

    printf("Sending %i packets of length %"PRIu16" to %"PRIu16"\n", count, size, addr);
    for (int i = 0; i < count; i++) {
        p.data = (uint8_t *) text_msg;
        p.length = size;
        p.dst = addr;
        mesg.type = SND_PKT;
        mesg.content.ptr = (char *)&tcmd;
        msg_send_receive(&mesg, &mesg, transceiver_pid);
        response = mesg.content.value;
        printf(".");
    }
    printf("\n");
}

void sc_traffic_gen(char *str)
{
    int count, size;
    radio_address_t addr;
    char *tok;
    
    if (strlen(str) < 3) {
        printf("usage: tg <count> <size> <address>\n");
        return;
    }

    tok = strtok(str + 2, " ");

    /* count */
    if (tok) {
        count = atoi(tok);
    }
    else {
        printf("no count given\n");
        return;
    }

    /* size */
    tok = strtok(NULL, " ");
    if (tok) {
        size = atoi(tok);
    }
    else {
        printf("no size given\n");
        return;
    }

    /* address */
    tok = strtok(NULL, " ");
    if (tok) {
        addr = atoi(tok);
    }
    else {
        printf("no address given\n");
        return;
    }

    /* run */
    traffic_gen(count, size, addr);
}

const shell_command_t shell_commands[] = {
    { "radio", "start/stop the radio thread", sc_start_stop_radio },
    { "tg", "send <count> packets of <size> to <addr>", sc_traffic_gen },
    { NULL, NULL, NULL }
};

int main(void)
{
    radio_pid = -1;

    /* initialize posix */
    posix_open(uart0_handler_pid, 0);

    /* initialize transceiver */
    printf("initializing and starting transceiver..");
    transceiver_init(TRANSCEIVER_TYPE);
    transceiver_start();
    printf(". done\n");

    /* XXX: too much convenience? */
    start_radio();

    /* initialize shell */
    shell_t shell;
    shell_init(&shell, shell_commands, shell_readc, shell_putchar);
    shell_run(&shell);

    return 0;
}

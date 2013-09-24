#include <stdio.h>
#include <string.h>
#include <transceiver.h>

#include <shell.h>
#include <board_uart0.h>
#include <posix_io.h>
#include <thread.h>
#include <board.h>
#include <hwtimer.h>
#include <vtimer.h>
#include <msg.h>
#include <cc110x_ng.h>

#define SHELL_STACK_SIZE    (KERNEL_CONF_STACKSIZE_DEFAULT + KERNEL_CONF_STACKSIZE_PRINTF)
#define RADIO_STACK_SIZE    (KERNEL_CONF_STACKSIZE_DEFAULT)

#ifdef MODULE_MSP430_COMMON
#define SND_BUFFER_SIZE     (10)
#define RCV_BUFFER_SIZE     (32)
#else
#define SND_BUFFER_SIZE     (100)
#define RCV_BUFFER_SIZE     (64)
#endif

#define SENDING_DELAY       (5 * 1000)

char shell_stack_buffer[SHELL_STACK_SIZE];
char radio_stack_buffer[RADIO_STACK_SIZE];

uint8_t snd_buffer[SND_BUFFER_SIZE][CC1100_MAX_DATA_LENGTH];

msg_t msg_q[RCV_BUFFER_SIZE];

static msg_t mesg;
static transceiver_command_t tcmd;
static radio_packet_t p;

static uint32_t sending_delay = SENDING_DELAY;

void sender(char *count);
void print_buffer(char *unused);
void switch2rx(char *unused);
void powerdown(char *unused);
void set_delay(char *delay);
#ifdef DBG_IGNORE
void ignore(char *addr);
#endif

shell_t shell;
const shell_command_t sc[] = {
    {"on", "", switch2rx},
    {"off", "", powerdown},
    {"snd", "", sender},
    {"delay", "", set_delay},
    {"buffer", "", print_buffer},
#ifdef DBG_IGNORE
    {"ign", "ignore node", ignore},
#endif
    {NULL, NULL, NULL}};

void shell_runner(void) {
    shell_init(&shell, sc, uart0_readc, uart0_putc);
    posix_open(uart0_handler_pid, 0);
    shell_run(&shell);
}

void sender(char *count) {
    unsigned int c, i;

    mesg.type = SND_PKT;
    mesg.content.ptr = (char*) &tcmd;

    tcmd.transceivers = TRANSCEIVER_CC1100;
    tcmd.data = &p;

    p.length = CC1100_MAX_DATA_LENGTH;
    p.dst = 0;

    c = atoi(count + strlen("snd "));
    for (i = 0; i < c; i++) {
        puts(".");
        p.data = snd_buffer[i % SND_BUFFER_SIZE];
        msg_send(&mesg, transceiver_pid, 1);
        vtimer_usleep(sending_delay);
    }
}

void print_buffer(char *unused) {
    uint8_t i;
    extern radio_packet_t transceiver_buffer[];
    for (i = 0; i < TRANSCEIVER_BUFFER_SIZE; i++) {
        printf("[%u] %u # %u # %u\n", i, transceiver_buffer[i].processing, transceiver_buffer[i].length, transceiver_buffer[i].data[i]);
    }
    extern rx_buffer_t cc110x_rx_buffer[];
    for (i = 0; i < TRANSCEIVER_BUFFER_SIZE; i++) {
        printf("[%u] %u # %u \n", i, cc110x_rx_buffer[i].packet.length, cc110x_rx_buffer[i].packet.data[i]);
    }
}

void switch2rx(char *unused) {
    mesg.type = SWITCH_RX;
    mesg.content.ptr = (char*) &tcmd;

    tcmd.transceivers = TRANSCEIVER_CC1100;
    puts("Turning transceiver on");
    if (msg_send(&mesg, transceiver_pid, 1)) {
        puts("\tsuccess");
    }
}

void powerdown(char *unused) {
    mesg.type = POWERDOWN;
    mesg.content.ptr = (char*) &tcmd;

    tcmd.transceivers = TRANSCEIVER_CC1100;
    puts("Turning transceiver off");
    if (msg_send(&mesg, transceiver_pid, 1)) {
        puts("\tsuccess");
    }
}

void set_delay(char *delay) {
    uint32_t d;

    d = atoi(delay + strlen("delay "));
    if (strlen(delay) > strlen("delay ")) {
        sending_delay = d;
    }
    else {
        puts("Usage:\tdelay <µs>");
    }
}

#ifdef DBG_IGNORE
void ignore(char *addr) {
    uint16_t a;
    mesg.type = DBG_IGN;
    mesg.content.ptr = (char*) &tcmd;

    tcmd.transceivers = TRANSCEIVER_CC1100;
    tcmd.data = &a;
    a = atoi(delay + strlen("ign "));
    if (strlen(addr) > strlen("ign ")) {
        printf("msg_q: %hu/%hu/%lu Transceiver PID: %i (%p), rx_buffer_next: %u\n", 
                msg_q[63].sender_pid, msg_q[63].type, msg_q[63].content.value, transceiver_pid, &transceiver_pid, rx_buffer_next);
        printf("sending to transceiver (%u): %u\n", transceiver_pid, (*(uint8_t*)tcmd.data));
        msg_send(&mesg, transceiver_pid, 1);
    }
    else {
        puts("Usage:\tign <addr>");
    }
}
#endif

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
            printf("\n");
        }
        else if (m.type == ENOBUFFER) {
            puts("Transceiver buffer full");
        }
        else {
            puts("Unknown packet received");
        }
    }
}

int main(void) {
    int radio_pid;
    uint8_t i;
    for (i = 0; i < SND_BUFFER_SIZE; i++) { 
        memset(snd_buffer[i], i, CC1100_MAX_DATA_LENGTH);
    }
    thread_create(shell_stack_buffer, SHELL_STACK_SIZE, PRIORITY_MAIN-1, CREATE_STACKTEST, shell_runner, "shell");
    radio_pid = thread_create(radio_stack_buffer, RADIO_STACK_SIZE, PRIORITY_MAIN-2, CREATE_STACKTEST, radio, "radio");
    transceiver_init(TRANSCEIVER_CC1100);
    transceiver_start();
    transceiver_register(TRANSCEIVER_CC1100, radio_pid);
   
   while (1) {
//       LED_GREEN_TOGGLE;
       hwtimer_wait(1000 * 1000);
   }
}

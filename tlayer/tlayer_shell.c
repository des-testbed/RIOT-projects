#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "thread.h"

#include "ltc4150.h"

#include "sixlowpan/sixlowpan.h"
#include "sixlowpan/sixlowborder.h"
#include "sixlowpan/sixlowerror.h"
#include "sixlowpan/sixlowmac.h"

#include "destiny/socket.h"

#include "net_help/net_help.h"
#include "net_help/msg_help.h"

#include "tlayer.h"

uint8_t tcp_send_pid = -1;
uint8_t tcp_server_thread_pid;

char tcp_server_stack_buffer[TCP_APP_STACK_SIZE];

uint8_t tcp_cht_pid;
char tcp_cht_stack_buffer[TCP_APP_STACK_SIZE];

char tcp_send_stack_buffer[SEND_TCP_THREAD_SIZE];

char tcp_close_thread_stack[TCP_CLOSE_THREAD_STACK_SIZE];

uint8_t udp_server_thread_pid;
char udp_server_stack_buffer[UDP_APP_STACK_SIZE];

/* initializes node */
void init(char *str)
{
    char command;
    uint16_t r_addr;
    ipv6_addr_t std_addr;

    int res = sscanf(str, "init %c %hu", &command, &r_addr);

    if(res < 1) {
        printf("Usage: init {h | r | a | e} radio_address\n");
        printf("\th\tinitialize as host\n");
        printf("\tr\tinitialize as router\n");
        printf("\ta\tinitialize as ad-hoc router\n");
        printf("\tb\tinitialize as border router\n\n");
        printf("\tradio_address must be an 8 bit integer\n");
    }

    ipv6_init_address(&std_addr, 0xABCD, 0, 0, 0, 0x1034, 0x00FF, 0xFE00, r_addr);

    switch(command) {
        case 'h':
            printf("INFO: Initialize as host on radio address %hu\n", r_addr);

            if(r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }

            sixlowpan_init(TRANSCEIVER_CC1100, r_addr, 0);
            break;

        case 'r':
            printf("INFO: Initialize as router on radio address %hu\n", r_addr);

            if(r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }

            sixlowpan_init(TRANSCEIVER_CC1100, r_addr, 0);
            ipv6_init_iface_as_router();
            break;

        case 'a':
            printf("INFO: Initialize as adhoc router on radio address %hu\n", r_addr);

            if(r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }

            sixlowpan_adhoc_init(TRANSCEIVER_CC1100, &std_addr, r_addr);
            break;

        case 'b':
            printf("INFO: Initialize as border router on radio address %hu\n", r_addr);

            if(r_addr > 255) {
                printf("ERROR: radio_address not an 8 bit integer\n");
                return;
            }

            res = border_initialize(TRANSCEIVER_CC1100, &std_addr);

            switch(res) {
                case(SUCCESS):
                    printf("INFO: Border router initialized.\n");
                    break;

                case(SIXLOWERROR_ADDRESS):
                    printf("ERROR: Illegal IP address: ");
                    ipv6_print_addr(&std_addr);
                    break;

                default:
                    printf("ERROR: Unknown error (%d).\n", res);
                    break;
            }

            break;

        default:
            printf("ERROR: Unknown command '%c'\n", command);
            break;
    }

    tcp_send_pid = thread_create(tcp_send_stack_buffer,
                                 SEND_TCP_THREAD_SIZE,
                                 PRIORITY_MAIN,
                                 CREATE_STACKTEST,
                                 send_tcp_thread,
                                 "send_tcp_thread");
}

/* performs 6lowpan bootstrapping */
void bootstrapping(char *str)
{
    sixlowpan_bootstrapping();
}

void boot_server(char *str)
{
    bootstrapping(NULL);
    vtimer_usleep(1000 * 1000 * 2);
    init_tcp_server_thread(NULL);
}

void boot_client(char *str)
{
    init_tcp_cht(NULL);
    vtimer_usleep(1000 * 1000 * 2);
    connect_tcp("connect_tcp 2");
}

/* prints current IPv6 adresses */
void ip(char *str)
{
    ipv6_iface_print_addrs();
}

/* shows 6lowpan context information */
void context(char *str)
{
    uint8_t i;
    lowpan_context_t *context;

    for(i = 0; i < LOWPAN_CONTEXT_MAX; i++) {
        context = lowpan_context_num_lookup(i);

        if(context != NULL) {
            printf("%2d\tLifetime: %5u\tLength: %3d\t", context->num, context->lifetime, context->length);
            ipv6_print_addr(&(context->prefix));
        }
    }
}

/* shows info about open sockets */
void shows(char *str)
{
    print_sockets();
}

/* shows reassembling buffer */
void showReas(char *str)
{
    printReasBuffers();
}

/* TODO: kill processes */
void kill_process(char *str)
{
    msg_t send;
    int mypid;
    send.type = RETURNNOW;
    sscanf(str, "kill_process %i", &mypid);
    msg_send(&send, mypid, 0);
}

/* Init TCP server thread */
void init_tcp_server_thread(char *str)
{
    tcp_server_thread_pid = thread_create(tcp_server_stack_buffer, TCP_APP_STACK_SIZE, PRIORITY_MAIN, CREATE_STACKTEST, init_tcp_server, "init_tcp_server");
    printf("TCP SERVER THREAD PID: %i\n", tcp_server_thread_pid);
}

/* Init TCP connection handler thread */
void init_tcp_cht(char *str)
{
    tcp_cht_pid = thread_create(tcp_cht_stack_buffer,
                                TCP_APP_STACK_SIZE,
                                PRIORITY_MAIN,
                                CREATE_STACKTEST,
                                tcp_ch,
                                "init_conn_handler");
    printf("TCP CONNECTION HANDLER THREAD PID: %i\n", tcp_cht_pid);
}

/* TCP send msg command */
void send_tcp_msg(char *str)
{
    msg_t send_msg, recv_msg;
    sscanf(str, "send_tcp %s", current_message.tcp_string_msg);

    if(strcmp(current_message.tcp_string_msg, "close") == 0) {
        send_msg.content.value = 0;
    }
    else {
        send_msg.content.value = 1;
    }

    msg_send_receive(&send_msg, &recv_msg, tcp_send_pid);
}

/* TCP send bulk command */
void send_tcp_bulk(char *str)
{
    int i = 0, count;
    char command[61];
    char msg_string[50];
    sscanf(str, "send_tcp_bulk %i %s", &count, msg_string);

    for(i = 0; i < count; i++) {
        sprintf(command, "send_tcp %s%.5i", msg_string, i);
        send_tcp_msg(command);
    }
}

/* TCP bandwidth test command */
void send_tcp_bandwidth_test(char *str)
{
    timex_t start, end, total;
    double secs;

    int i = 0, count;
    char command[80];
    char msg_string[] = "abcdefghijklmnopqrstuvwxyz0123456789!-=/%$";

    sscanf(str, "tcp_bw %i", &count);
    ltc4150_start();
    printf("Start power: %f\n", ltc4150_get_total_mAh());
    vtimer_now(&start);

    for(i = 0; i < count; i++) {
        sprintf(command, "send_tcp %s%.5i", msg_string, i);
        send_tcp_msg(command);
    }

    vtimer_now(&end);
    total = timex_sub(end, start);
    secs = total.microseconds / 1000000.0f;
    printf("Used power: %f\n", ltc4150_get_total_Joule());
    printf("Start: %lu, End: %lu, Total: %lu\n", start.microseconds, end.microseconds, total.microseconds);
    printf("Time: %f seconds, Bandwidth: %f byte/second\n", secs, (count * 48) / secs);
}

/* TCP connect command */
void connect_tcp(char *str)
{
    msg_t send_msg;
    sscanf(str, "connect_tcp %i", &current_message.node_number);
    send_msg.content.value = 1;
    msg_send(&send_msg, tcp_cht_pid, 0);
}

/* TCP disconnect command */
void disconnect_tcp(char *str)
{
    msg_t send_msg;

    send_msg.content.value = 0;
    msg_send(&send_msg, tcp_cht_pid, 0);
}

/* UDP server thread */
void init_udp_server_thread(char *str)
{
    udp_server_thread_pid = thread_create(udp_server_stack_buffer, UDP_APP_STACK_SIZE, PRIORITY_MAIN, CREATE_STACKTEST, init_udp_server, "init_udp_server");
    printf("UDP SERVER THREAD PID: %i\n", udp_server_thread_pid);
}

/* UDP send command */
void send_udp(char *str)
{
    timex_t start, end, total;
    long secs;
    int sock;
    sockaddr6_t sa;
    ipv6_addr_t ipaddr;
    int bytes_sent;
    int address, count;
    char text[] = "abcdefghijklmnopqrstuvwxyz0123456789!-=$%&/()";
    sscanf(str, "send_udp %i %i %s", &count, &address, text);

    sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);

    if(-1 == sock) {
        printf("Error Creating Socket!");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof sa);

    ipv6_init_address(&ipaddr, 0xabcd, 0x0, 0x0, 0x0, 0x3612, 0x00ff, 0xfe00, (uint16_t)address);
    ipv6_print_addr(&ipaddr);

    sa.sin6_family = AF_INET;
    memcpy(&sa.sin6_addr, &ipaddr, 16);
    sa.sin6_port = HTONS(7654);
    ltc4150_start();
    printf("Start power: %f\n", ltc4150_get_total_Joule());
    vtimer_now(&start);

    for(int i = 0; i < count; i++) {
        bytes_sent = sendto(sock, (char *)text, strlen((char *)text) + 1, 0, &sa, sizeof sa);

        if(bytes_sent < 0) {
            printf("Error sending packet!\n");
        }

        /* 	hwtimer_wait(20*1000); */
    }

    vtimer_now(&end);
    total = timex_sub(end, start);
    secs = total.microseconds / 1000000;
    printf("Used power: %f\n", ltc4150_get_total_Joule());
    printf("Start: %lu, End: %lu, Total: %lu\n", start.microseconds, end.microseconds, total.microseconds);
    secs = total.microseconds / 1000000;
    printf("Time: %lu seconds, Bandwidth: %lu byte/second\n", secs, (count * 48) / secs);
    close(sock);
}

void close_tcp(char *str)
{
    thread_create(tcp_close_thread_stack, TCP_CLOSE_THREAD_STACK_SIZE, PRIORITY_MAIN,
                  CREATE_STACKTEST, close_tcp_thread, "tcp_close_thread");
}

void print_fragment_counter(char *str)
{
    printf("Fragment Counter: %u\n", fragmentcounter);
}

void pfifo_buf(char *str)
{
    printFIFOBuffers();
}

void get_rtt(char *str)
{
    int socket;
    sscanf(str, "get_rtt %i", &socket);
    printf("SRTT: %f, RTO: %f, RTTVAR: %f\n", getSocket(socket)->socket_values.tcp_control.srtt,
           getSocket(socket)->socket_values.tcp_control.rto,
           getSocket(socket)->socket_values.tcp_control.rttvar);
}

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "transceiver.h"

#include "destiny/tcp.h"
#include "destiny/socket.h"

#include "net_help/net_help.h"

#include "tlayer.h"

tcp_message_t current_message;
static uint8_t running_recv_threads = 0;
static uint8_t recv_socket_id1 = 0;
static uint8_t recv_socket_id2 = 0;

/* Socket ID used for sending/receiving packets via different threads */
int tcp_socket_id = -1;

char tcp_server_stack_buffer[TCP_APP_STACK_SIZE];

void recv_from_tcp_thread1(void);
void recv_from_tcp_thread2(void);
char recv_from_tcp_thread_stack1[RECV_FROM_TCP_THREAD_STACK_SIZE1];
char recv_from_tcp_thread_stack2[RECV_FROM_TCP_THREAD_STACK_SIZE2];

void init_tcp_server(void)
{
    sockaddr6_t stSockAddr;
    int read_bytes;
    char buff_msg[MAX_TCP_BUFFER];
    int16_t a;
    transceiver_command_t tcmd;
    msg_t mesg;

    memset(buff_msg, 0, MAX_TCP_BUFFER);
    int SocketFD = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if(-1 == SocketFD) {
        perror("can not create socket");
        exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(stSockAddr));

    stSockAddr.sin6_family = AF_INET6;
    stSockAddr.sin6_port = HTONS(1100);

    tcmd.transceivers = TRANSCEIVER_CC1100;
    mesg.type = GET_ADDRESS;
    tcmd.data = &a;
    mesg.content.ptr = (char *) &tcmd;
    msg_send_receive(&mesg, &mesg, transceiver_pid);

    ipv6_init_address(&stSockAddr.sin6_addr, 0xabcd, 0x0, 0x0, 0x0, 0x3612, 0x00ff, 0xfe00, a);
    ipv6_print_addr(&stSockAddr.sin6_addr);

    if(-1 == bind(SocketFD, &stSockAddr, sizeof(stSockAddr))) {
        printf("error bind failed\n");
        close(SocketFD);
        return;
    }

    print_internal_socket(getSocket(SocketFD));

    if(-1 == listen(SocketFD, 10)) {
        printf("error listen failed\n");
        close(SocketFD);
        return;
    }

    while(1) {
        read_bytes = 0;
        printf("INFO: WAITING FOR INC CONNECTIONS!\n");
        int ConnectFD = accept(SocketFD, NULL, 0);

        if(0 > ConnectFD) {
            printf("error accept failed\n");
            close(SocketFD);
            return;
        }
        else {
            printf("Connection established on socket %u.\n", ConnectFD);

            if(running_recv_threads == 0) {
                recv_socket_id1 = ConnectFD;
                thread_create(recv_from_tcp_thread_stack1, RECV_FROM_TCP_THREAD_STACK_SIZE1, PRIORITY_MAIN,
                              CREATE_STACKTEST, recv_from_tcp_thread1, "recv_from_tcp_thread1");
            }
            else if(running_recv_threads == 1) {
                recv_socket_id2 = ConnectFD;
                thread_create(recv_from_tcp_thread_stack2, RECV_FROM_TCP_THREAD_STACK_SIZE2, PRIORITY_MAIN,
                              CREATE_STACKTEST, recv_from_tcp_thread2, "recv_from_tcp_thread2");
            }

            running_recv_threads++;
        }
    }
}

/* TCP connection handler */
void tcp_ch(void)
{
    msg_t recv_msg;
    int read_bytes = 0;
    char buff_msg[MAX_TCP_BUFFER];
    sockaddr6_t stSockAddr;
    msg_receive(&recv_msg);
    int SocketFD = socket(PF_INET6, SOCK_STREAM, IPPROTO_TCP);

    if(-1 == SocketFD) {
        printf("cannot create socket");
        return;
    }

    memset(&stSockAddr, 0, sizeof(stSockAddr));

    stSockAddr.sin6_family = AF_INET6;
    stSockAddr.sin6_port = HTONS(1100);

    ipv6_init_address(&stSockAddr.sin6_addr, 0xabcd, 0x0, 0x0, 0x0, 0x3612, 0x00ff, 0xfe00, current_message.node_number);
    ipv6_print_addr(&stSockAddr.sin6_addr);

    if(-1 == connect(SocketFD, &stSockAddr, sizeof(stSockAddr))) {
        printf("Connect failed!\n");
        close(SocketFD);
        return;
    }

    tcp_socket_id = SocketFD;

    while(read_bytes != -1) {
        read_bytes = recv(SocketFD, buff_msg, MAX_TCP_BUFFER, 0);

        if(read_bytes > 0) {
            printf("--- Message: %s ---\n", buff_msg);
        }

    }
}


/* TCP sender thread */
void send_tcp_thread(void)
{
    msg_t recv_msg, send_msg;

    while(1) {
        msg_receive(&recv_msg);

        if(tcp_socket_id == -1) {
            tcp_socket_id = recv_socket_id1;
        }

        if(send(tcp_socket_id, (void *) current_message.tcp_string_msg, strlen(current_message.tcp_string_msg) + 1, 0) < 0) {
            printf("Could not send %s!\n", current_message.tcp_string_msg);
        }

        msg_reply(&recv_msg, &send_msg);
    }
}

/* TCP receiver thread 1 */
void recv_from_tcp_thread1(void)
{
    int read_bytes = 0;
    char buff_msg[MAX_TCP_BUFFER];
    memset(buff_msg, 0, MAX_TCP_BUFFER);

    while(read_bytes != -1) {
        read_bytes = recv(recv_socket_id1, buff_msg, MAX_TCP_BUFFER, 0);

        if(read_bytes > 0) {
            puts(".");
            /* 		printf("--- Read bytes: %i, Strlen(): %i, Message: %s ---\n", read_bytes, strlen(buff_msg), buff_msg); */
        }
    }
}

/* TCP receiver thread 2 */
void recv_from_tcp_thread2(void)
{
    int read_bytes = 0;
    char buff_msg[MAX_TCP_BUFFER];
    memset(buff_msg, 0, MAX_TCP_BUFFER);

    while(read_bytes != -1) {
        read_bytes = recv(recv_socket_id2, buff_msg, MAX_TCP_BUFFER, 0);

        if(read_bytes > 0) {
            /* 		printf("--- Read bytes: %i, Strlen(): %i, Message: %s ---\n", read_bytes, strlen(buff_msg), buff_msg); */
        }
    }
}

void close_tcp_thread(void)
{
    close(tcp_socket_id);
}

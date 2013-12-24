#include <stdint.h>
#include <stdio.h>

#include "destiny.h"
#include "shell.h"
#include "posix_io.h"
#include "board_uart0.h"

#include "tlayer.h"

#ifdef DBG_IGNORE
static msg_t mesg;
static transceiver_command_t tcmd;
#endif

void init_tl(char *str)
{
    destiny_init_transport_layer();
}

#ifdef DBG_IGNORE
void ignore(char *addr)
{
    uint16_t a;
    mesg.type = DBG_IGN;
    mesg.content.ptr = (char *) &tcmd;

    tcmd.transceivers = TRANSCEIVER;
    tcmd.data = &a;

    if(sscanf(addr, "ign %hu", &a) == 1) {
        msg_send(&mesg, transceiver_pid, 1);
    }
    else {
        puts("Usage:\tign <addr>");
    }
}
#endif

const shell_command_t shell_commands[] = {
    {"init", "initializes node", init},
    {"boot", "performs 6lowpan bootstrapping", bootstrapping},
    {"ip", "shows current IPv6 addresses", ip},
    {"shows", "Show Sockets", shows},
    {"context", "shows 6lowpan context information", context},
    {"init_udp_server_thread", "initializes UDP server", init_udp_server_thread},
    {"init_tcp_server_thread", "initializes TCP server", init_tcp_server_thread},
    {"init_tcp_cht", "initializes TCP connection handler", init_tcp_cht},
    {"connect_tcp", "performs TCP connect", connect_tcp},
    {"send_tcp", "Send a TCP message", send_tcp_msg},
    {"send_udp", "Send a UDP message", send_udp},
    {"send_tcp_bulk", "send_tcp_bulk NO_OF_PACKETS PAYLOAD", send_tcp_bulk},
    {"kill_process", "", kill_process},
    {"close_tcp", "Closes a TCP connection", close_tcp},
    {"tcp_bw", "tcp_bw NO_OF_PACKETS", send_tcp_bandwidth_test},
    {"boots", "start node as TCP server", boot_server},
    {"bootc", "start node as TCP client", boot_client},
#ifdef ENABLE_DEBUG
    {"show_reas", "Show reassembly Buffers", showReas},
    {"show_fifo", "prints fifo", pfifo_buf},
#endif
#ifdef DBG_IGNORE
    {"ign", "ignore node", ignore},
#endif
    {NULL, NULL, NULL}
};

int main(void)
{
    printf("6LoWPAN Transport Layers\n");
    posix_open(uart0_handler_pid, 0);

    init_tl(NULL);

    shell_t shell;
    shell_init(&shell, shell_commands, UART0_BUFSIZE, uart0_readc, uart0_putc);

    shell_run(&shell);

    return 0;
}

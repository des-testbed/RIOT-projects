#ifndef TLAYER_H
#define TLAYER_H

#define SEND_TCP_THREAD_SIZE				(4500)
#define TCP_CLOSE_THREAD_STACK_SIZE			(4500)
#define RECV_FROM_TCP_THREAD_STACK_SIZE1	(500)
#define RECV_FROM_TCP_THREAD_STACK_SIZE2	(500)
#define UDP_APP_STACK_SIZE					(4500)
#define TCP_APP_STACK_SIZE					(4500)

typedef struct {
    int		 	node_number;
    char		tcp_string_msg[80];
} tcp_message_t;

extern uint8_t tcp_cht_pid;
extern uint8_t udp_server_thread_pid;
extern uint8_t tcp_server_thread_pid;

extern tcp_message_t current_message;

/* shell commands */
void init(char *str);
void bootstrapping(char *str);
void boot_server(char *str);
void boot_client(char *str);
void ip(char *str);
void context(char *str);
void shows(char *str);
void showReas(char *str);
void kill_process(char *str);
void init_tcp_server_thread(char *str);
void init_udp_server_thread(char *str);
void init_tcp_cht(char *str);
void send_tcp_msg(char *str);
void send_tcp_bulk(char *str);
void send_tcp_bandwidth_test(char *str);
void connect_tcp(char *str);
void disconnect_tcp(char *str);
void send_udp(char *str);
void close_tcp(char *str);
void show_nbr_cache(char *str);
void static_routing(char *str);
void print_fragment_counter(char *str);
void pfifo_buf(char *str);
void get_rtt(char *str);

void init_tcp_server(void);
void send_tcp_thread(void);
void tcp_ch(void);
void close_tcp_thread(void);

void init_udp_server(void);

#endif /* TLAYER_H */

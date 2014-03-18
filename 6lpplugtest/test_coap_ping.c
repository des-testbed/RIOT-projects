#include "test_coap_ping.h"
#include "test_utils.h"

#ifdef MODULE_LIBCOAP
#include <netinet/in.h>

#include "coap.h"
#include "cpu-conf.h"
#include "thread.h"
#include "ipv6.h"
#include "transceiver.h"

#define COAP_SERVER_STACK_SIZE  (4 * MINIMUM_STACK_SIZE)
#define COAP_SERVER_PORT        (UPPER_LAYER_5)

char coap_server_stack[COAP_SERVER_STACK_SIZE];

coap_context_t *get_context(ipv6_addr_t *node, uint16_t port)
{
    coap_address_t addr;
    
    memset(&addr, 0, sizeof(coap_address_t));
    if (node != NULL) {
        memcpy(&addr.addr.sin6.sin6_addr, node, sizeof (struct in6_addr));
    }

    addr.size = sizeof(struct sockaddr_in6);
    addr.addr.sin6.sin6_family = AF_INET6;
    addr.addr.sin6.sin6_port = (in_port_t)port;
    
    return coap_new_context(&addr); 
}

int slpt_coap_send_ping(uint16_t local_port, const ipv6_addr_t *node,
                        uint16_t node_port)
{
    coap_address_t addr;
    coap_context_t *ctx = get_context(NULL, local_port);
    coap_hdr_t hdr;
    coap_pdu_t pdu;

    if (!ctx) {
        ERROR("Could not initialize CoAP context\n");
    }

    memset(&hdr, 0, sizeof (coap_hdr_t));
    hdr.version = 1;

    memset(&pdu, 0, sizeof (coap_pdu_t));
    pdu.hdr = &hdr;
    pdu.length = 4;

    memset(&addr, 0, sizeof(coap_address_t));
    memcpy(&addr.addr.sin6.sin6_addr, node, sizeof (struct in6_addr));
    addr.size = sizeof(struct sockaddr_in6);
    addr.addr.sin6.sin6_family = AF_INET6;
    addr.addr.sin6.sin6_port = (in_port_t)node_port;
    
    coap_send_confirmed(ctx, &addr, &pdu);

    return 1;
}

void coap_server_process(void)
{
    msg_t msg;
    uint16_t server_port;
    coap_context_t *ctx;

    msg.type = 0;

    while (msg.type != COAP_SERVER_PORT) {
        msg_receive(&msg);
    }

    server_port = (uint16_t) msg.content.value;
    ctx = get_context(NULL, server_port);
    if (!ctx) {
        return;
    }
    
    while (1) {
        if (coap_read(ctx) >= 0) {
            coap_dispatch(ctx);
            return;
        }
    }
}

int slpt_coap_run_server(uint16_t server_port)
{
    msg_t msg;
    int pid;

    if (!slplugtest_utils_initialize_queue()) {
        return -1;
    }

    pid = thread_create(coap_server_stack, COAP_SERVER_STACK_SIZE,
                        PRIORITY_MAIN - 1, CREATE_STACKTEST,
                        coap_server_process, "coap ping server");    

    msg.type = COAP_SERVER_PORT;
    msg.content.value = (uint32_t) server_port;

    if (msg_send(&msg, pid, 0) != 1) {
        return -1;
    }

    return pid;
}
#endif

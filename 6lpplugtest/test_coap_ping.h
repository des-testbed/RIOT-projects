#include "ipv6.h"
#include "inttypes.h"


int slpt_coap_send_ping(uint16_t local_port, const ipv6_addr_t *node,
                        uint16_t node_port);
int slpt_coap_run_server(uint16_t server_port);

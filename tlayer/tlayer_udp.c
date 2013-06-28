#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "destiny/socket.h"
#include "destiny/udp.h"

#include "net_help/net_help.h"

void init_udp_server(void)
{
    sockaddr6_t sa;
    char buffer_main[256];
    int32_t recsize;
    uint32_t fromlen;
    int sock = socket(PF_INET6, SOCK_DGRAM, IPPROTO_UDP);
    memset(&sa, 0, sizeof(sa));

    sa.sin6_family = AF_INET;
    sa.sin6_port = HTONS(7654);

    fromlen = sizeof(sa);

    if(-1 == bind(sock, &sa, sizeof(sa))) {
        printf("Error bind failed!\n");
        close(sock);
    }

    for(;;) {
        recsize = recvfrom(sock, (void *)buffer_main, 256, 0, &sa, &fromlen);

        if(recsize < 0) {
            printf("ERROR: recsize < 0!\n");
        }

        printf("recsize: %"PRIi32"\n ", recsize);
        printf("datagram: %s\n", buffer_main);
    }

    close(sock);
}


/*
 * Copyright (C) 2013 Christian Mehlis <christian.mehlis@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "net_if.h"
#include "transceiver.h"

#ifndef TRANSCEIVER
#ifdef MODULE_CC110X_NG
#define TRANSCEIVER (TRANSCEIVER_CC1100)
#elif MOTULE_NETNATIVE
#define TRANSCEIVER (TRANSCEIVER_NATIVE)
#endif
#endif

int main(void)
{
    int iface, count = 0;
    char *addr1_data = "abcdefgh", *addr2_data = "12345678";
    net_if_addr_t addr1 = {
        .addr_next = NULL,
        .addr_prev = NULL,
        .addr_protocol = NET_IF_L3P_IPV6_STATIC,
        .addr_data = (void *)addr1_data,
        .addr_len = (strlen(addr1_data)+1)*8
    };
    net_if_addr_t addr2 = {
        .addr_next = NULL,
        .addr_prev = NULL,
        .addr_protocol = NET_IF_L3P_IPV6_AUTO,
        .addr_data = (void *)addr2_data,
        .addr_len = (strlen(addr2_data)+1)*8
    };
    net_if_addr_t *addr_ptr = NULL;
    transceiver_addr_t own = 1, target = 2, tmp;
    net_if_eui64_t eui64;

    transceiver_init(TRANSCEIVER);
    transceiver_start();
#ifndef MODULE_AUTO_INIT
    net_if_init();
#endif

    iface = net_if_init_interface(NET_IF_L3P_6LOWPAN, TRANSCEIVER);

    if (!(net_if_get_l3p_types(iface) & NET_IF_L3P_6LOWPAN)) {
        printf("L3 type 6LoWPAN expected on interface %d.\n", iface);
        return -1;
    }

    if (net_if_get_l3p_types(iface) & ~NET_IF_L3P_6LOWPAN) {
        printf("L3 type other than 6LoWPAN not expected on interface %d.\n", 
               iface);
        return -1;
    }

    if (net_if_iter_addresses(iface + 1, &addr_ptr)) {
        printf("Expected error on interface '%d'\n", iface + 1);
        return -1;
    }

    if (net_if_iter_addresses(iface, &addr_ptr)) {
        printf("Expected error on interface '%d'\n", iface);
        return -1;
    }

    net_if_add_address(iface, &addr1);

    if (!(net_if_get_l3p_types(iface) & NET_IF_L3P_6LOWPAN)) {
        printf("L3 type 6LoWPAN expected on interface %d.\n", iface);
        return -1;
    }

    if (!(net_if_get_l3p_types(iface) & NET_IF_L3P_IPV6_STATIC)) {
        printf("L3 type IPv6 static expected on interface %d.\n", iface);
        return -1;
    }

    if (net_if_get_l3p_types(iface) & ~(NET_IF_L3P_6LOWPAN | NET_IF_L3P_IPV6_STATIC)) {
        printf("L3 type other than 6LoWPAN and IPv6 static not expected on interface %d.\n", 
               iface);
        return -1;
    }

    net_if_add_address(iface, &addr2);

    if (!(net_if_get_l3p_types(iface) & NET_IF_L3P_6LOWPAN)) {
        printf("L3 type 6LoWPAN expected on interface %d.\n", iface);
        return -1;
    }

    if (!(net_if_get_l3p_types(iface) & NET_IF_L3P_IPV6_STATIC)) {
        printf("L3 type IPv6 static expected on interface %d.\n", iface);
        return -1;
    }

    if (!(net_if_get_l3p_types(iface) & NET_IF_L3P_IPV6_AUTO)) {
        printf("L3 type IPv6 auto static expected on interface %d.\n", iface);
        return -1;
    }

    if (net_if_get_l3p_types(iface) & ~(NET_IF_L3P_6LOWPAN | NET_IF_L3P_IPV6_STATIC | NET_IF_L3P_IPV6_AUTO)) {
        printf("L3 type other than 6LoWPAN, IPv6 static, and IPv6 auto not expected on interface %d.\n", 
               iface);
        return -1;
    }

    while (net_if_iter_addresses(iface, &addr_ptr)) {
        if (addr_ptr == &addr1  || addr_ptr == &addr2) {
            count++;
        }
    }

    if (count != 2) {
        printf("'%s' and '%s' expected in iface's address list once respectively\n", 
               addr1_data, addr2_data);
        printf("missing '%d'\n", 2-count);
        return -1;
    }

    count = 0;
    net_if_del_address(iface, &addr1);

    while (net_if_iter_addresses(iface, &addr_ptr)) {
        if (addr_ptr == &addr1 || addr_ptr == &addr2) {
            count++;
        }
    }

    if (count != 1) {
        printf("'%s' expected in iface's address list once\n", addr2_data);
        printf("missing '%d'\n", 1-count);
        return -1;
    }

    count = 0;
    net_if_del_l3p_types(iface, NET_IF_L3P_IPV6_AUTO);

    while (net_if_iter_addresses(iface, &addr_ptr)) {
        if (addr_ptr == &addr1 || addr_ptr == &addr2) {
            count++;
        }
    }

    tmp = net_if_set_hardware_address(iface, own);
    if (own != tmp) {
        printf("Expected '%d' as result of net_if_set_hardware_addr() "
               "(was '%d')\n", own, tmp);
        return -1;
    }

    tmp = net_if_get_hardware_address(iface);
    if (own != tmp) {
        printf("Expected '%d' as result of net_if_get_hardware_addr() "
               "(was '%d')\n", own, tmp);
        return -1;
    }

    if (!net_if_get_eui64(&eui64, iface, 1)) {
        printf("Error getting EUI-64 on interface %d\n", iface);
        return -1;
    }

    if ((transceiver_addr_t)eui64.uint16[3] != own) {
        printf("Expected last 16 bit of EUI-64 to be 0x%04x (is 0x%04x)\n", own,
               eui64.uint16[3]);
        return -1;
    }

    if (count != 0) {
        printf("No address expected in iface's address list\n");
        printf("Addresses '%d'\n", count);
        return -1;
    }

    if (net_if_iter_addresses(iface, &addr_ptr)) {
        printf("Expected error on interface '%d'\n", iface);
        return -1;
    }

    count = net_if_send_packet(iface, target, "Test", 4);

    printf("Count was %i after net_if_send_packet()\n", count);

    printf("All test ran successfully.\n");

    return 0;
}

/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "ipv6.h"
#include "msg.h"
#include "inet_ntop.h"
#include "inet_pton.h"
#include "net_help.h"
#include "sixlowpan.h"
#include "test_utils.h"
#include "thread.h"

#define RCV_BUFFER_SIZE (2048)
#define MIN(a, b)   (((a) < (b)) ? (a) : (b))

static uint8_t registered_to_lowpan = 0; 
static uint8_t registered_to_ipv6 = 0; 
static uint8_t queue_initialized = 0;

static msg_t msg_q[RCV_BUFFER_SIZE];

int slplugtest_utils_isnumber(char *str)
{
    for (; *str; str++) {
        if (!isdigit((int)*str)) {
            return 0;
        }
    }

    return 1;
}

uint8_t slplugtest_utils_hex_to_dec(char c)
{
    if (c >= '0' && c <= '9') {
        return (uint8_t)(c - '0');
    }
    else if (c >= 'A' && c <= 'F') {
        return (uint8_t)(c - 55);
    }
    else if (c >= 'a' && c <= 'f') {
        return (uint8_t)(c - 87);
    }
    else {
        return 0xff;
    }
}

void slplugtest_utils_generate_data(char *data_out, char *data_in, size_t data_len)
{
    char *tmp;
    size_t current_len = strlen(data_in);

    memset(data_out, 0, data_len + 1);
    
    for (tmp = data_out; strlen(data_out) < data_len; tmp += strlen(data_in)) {
        size_t cpy_len = (current_len < data_len) ? strlen(data_in) : data_len;

        if (current_len + cpy_len > data_len) {
            cpy_len = data_len - current_len;
        }

        memcpy(tmp, data_in, cpy_len);
    } 
}

void slplugtest_utils_str_to_eui64(net_if_eui64_t *eui64, char *eui64_str)
{
    if (slplugtest_utils_isnumber(eui64_str)) {
        eui64->uint64 = HTONLL((uint64_t)atol(eui64_str));
    }
    else {
        int i;
        char *eui64_rev = &eui64_str[strlen(eui64_str) - 1];
        eui64->uint64 = 0;

        for (i = 7; i >= 0 || eui64_rev >= eui64_str; i--) {
            uint8_t digit;

            while ((digit = slplugtest_utils_hex_to_dec(*eui64_rev)) == 0xFF) {
                if (--eui64_rev < eui64_str) {
                    goto ret;
                }
            }

            eui64->uint8[i] = digit;
            eui64_rev--;

            while ((digit = slplugtest_utils_hex_to_dec(*eui64_rev)) == 0xFF) {
                if (--eui64_rev < eui64_str) {
                    goto ret;
                }
            }

            eui64->uint8[i] |= digit << 4;
            eui64_rev--;
        }

    ret:
        return;
    }
}

uint8_t slplugtest_utils_init_eut_addr(ipv6_addr_t *eut_addr, char *eut_addr_str)
{
    int res;

    if (eut_addr_str == NULL) {
        ERROR("Destination is not defined.\n");
    }

    res = inet_pton(AF_INET6, eut_addr_str, eut_addr);

    if (res == 0) {
        ERROR("Given string is no IPv6 address\n");
    }

    if (res < 0) {
        ERROR("Unexpected error in address initialization\n");
    }

    return 1;
}

uint8_t slplugtest_utils_init_ll_eut_addr(ipv6_addr_t *eut_addr, char *eut_addr_str)
{
    if (!slplugtest_utils_init_eut_addr(eut_addr, eut_addr_str)) {
        SILENT_ERROR();
    }

    if (!ipv6_addr_is_link_local(eut_addr)) {
        ERROR("Destination is not a link-local address.\n");
    }
    
    return 1;
}

uint8_t slplugtest_utils_init_prefix(ipv6_addr_t *prefix, int *prefix_len,
                                     char *prefix_str)
{
    char prefix_str_cpy[IPV6_MAX_ADDR_STR_LEN + 8], *tmp;

    if (!prefix_str) {
        return 0;
    }

    strcpy(prefix_str_cpy, prefix_str);
    tmp = (char *)&prefix_str_cpy[0];

    for (; *tmp != '/' && *tmp != '\0'; tmp++);

    if (*tmp) {
        tmp++;
        *(tmp-1) = '\0';
        *prefix_len = atoi(tmp);
    }
    else {
        *prefix_len = 128;
    }

    if (!slplugtest_utils_init_eut_addr(prefix, prefix_str_cpy)) {
        return 0;
    }

    return 1;
}

void slplugtest_utils_print_bytestream(uint8_t *bytes, uint16_t len) {
    for (int i = 0; i < len; i++) {
        printf("%02x ", bytes[i]);
        if ((i+1) % 20 == 0) {
            printf("\n");
        }
    }
    if (len % 20 != 0) {
        printf("\n");
    }
}

uint8_t slplugtest_utils_initialize_queue(void)
{
    if (queue_initialized) {
        return 1;
    }
    else {
        queue_initialized = 1;
        return msg_init_queue(msg_q, RCV_BUFFER_SIZE) == 0; 
    }
}

uint8_t slplugtest_utils_register_to_lowpan(void)
{
    if (registered_to_lowpan) {
        return 1;
    }
    else {
        if (sixlowpan_lowpan_register(thread_getpid()) == 1) {
            registered_to_lowpan = 1;
            return 1;
        }
        return 0;
    }
}

uint8_t slplugtest_utils_register_to_ipv6(void)
{
    if (registered_to_ipv6) {
        return 1;
    }
    else {
        registered_to_ipv6 = 1;
        if (ipv6_register_packet_handler(thread_getpid()) == 1) {
            registered_to_ipv6 = 1;
            return 1;
        }
        return 0;
    }
}

uint8_t slplugtest_utils_check_dispatch(sixlowpan_lowpan_frame_t *data,
                                        uint8_t *disp, uint8_t *disp_mask,
                                        uint8_t disp_len)
{
    if (data->length < disp_len) {
        return 0;
    }    

    printf("6LoWPAN dispatch was: ");
    slplugtest_utils_print_bytestream(data->data, disp_len);

    for (int i = 0; i < disp_len; i++) {
        if ((data->data[i] & disp_mask[i]) != disp[i]) {
            return 0;
        }
    }
    return 1;
}

uint8_t slplugtest_utils_check_sender(ipv6_hdr_t *header, ipv6_addr_t *addr)
{
    char str[41];
    printf("sender was: %s\n", inet_ntop(AF_INET6, addr, str, 41));
    return ipv6_addr_is_equal(&header->srcaddr, addr);
}

uint8_t slplugtest_utils_check_echo_data(uint8_t *packet, uint8_t *data,
                                         uint8_t data_len)
{
    ipv6_hdr_t *header = (ipv6_hdr_t *)packet;

    if (header->length < 48 + data_len) {
        return 0;
    }

    printf("echo data was:\n");
    slplugtest_utils_print_bytestream(data, data_len);

    return memcmp(&packet[48], data, data_len) == 0;
}

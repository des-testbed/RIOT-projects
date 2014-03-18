/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */
#include "inet_ntop.h"
#include "ipv6.h"
#include "msg.h"
#include "net_if.h"
#include "sixlowpan.h"

#include "test_format.h"
#include "test_utils.h"

#if defined(MODULE_SHELL) || defined(FORMAT)
int sixlowpan_format_init(void)
{
    ipv6_addr_t tmp;
    char addr_str[IPV6_MAX_ADDR_STR_LEN];

    sixlowpan_lowpan_set_iphc_status(LOWPAN_IPHC_DISABLE);
    ipv6_addr_set_link_local_prefix(&tmp);

#if 0
    if (net_if_set_channel(IF_ID, CHANNEL) < 0) {
        printf("Can not set channel %d.\n", CHANNEL);
        return 0;
    }

    if (net_if_set_pan_id(IF_ID, PAN_ID) < 0) {
        printf("Can not set PAN ID %d.\n", PAN_ID);
        return 0;
    }
#endif

    if (!ipv6_addr_set_by_eui64(&tmp, IF_ID, &tmp)) {
        printf("Can not set link-local by EUI-64 on interface %d\n", IF_ID);
        return 0;
    }

    printf("Add link local address to interface %d: %s\n", IF_ID,
           inet_ntop(AF_INET6, &tmp, addr_str, IPV6_MAX_ADDR_STR_LEN));

    if (!ipv6_net_if_add_addr(IF_ID, &tmp, NDP_ADDR_STATE_PREFERRED,
                              NDP_OPT_PI_VLIFETIME_INFINITE,
                              NDP_OPT_PI_PLIFETIME_INFINITE, 0)) {
        printf("Can not add link-local address to interface %d\n", IF_ID);
        return 0;
    }

    /* add all nodes multicast address */
    ipv6_addr_set_all_nodes_addr(&tmp);
    printf("Add all nodes multicast address to interface %d: %s\n", IF_ID,
           inet_ntop(AF_INET6, &tmp, addr_str, IPV6_MAX_ADDR_STR_LEN));

    if (!ipv6_net_if_add_addr(IF_ID, &tmp, NDP_ADDR_STATE_PREFERRED,
                              NDP_OPT_PI_VLIFETIME_INFINITE,
                              NDP_OPT_PI_PLIFETIME_INFINITE, 0)) {
        printf("Can not add all nodes address to interface %d\n", IF_ID);
        return 0;
    }
    
    return 1;
}

int sixlowpan_format_init_long(ipv6_addr_t *eut_addr)
{
    net_if_eui64_t eut_eui64;

    memcpy(&eut_eui64, &eut_addr->uint8[8], 8);
    eut_eui64.uint8[0] ^= 0x02;

    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_LONG);
    return sixlowpan_format_init() && (eut_addr == NULL ||
           ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_eui64, 8, 0,
                                  NDP_NCE_STATUS_REACHABLE,
                                  NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                    NDP_OPT_ARO_STATE_SUCCESS); 
}

int sixlowpan_format_init_short(ipv6_addr_t *eut_addr)
{
    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_SHORT);
    return sixlowpan_format_init() && (eut_addr == NULL ||
           ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_addr->uint16[7], 2, 0,
                                  NDP_NCE_STATUS_REACHABLE,
                                  NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                    NDP_OPT_ARO_STATE_SUCCESS); 
}

int sixlowpan_format_init_src_long_dst_short(ipv6_addr_t *eut_addr)
{
    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_LONG);
    return sixlowpan_format_init() && (eut_addr == NULL ||
           ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_addr->uint16[7], 2, 0,
                                  NDP_NCE_STATUS_REACHABLE,
                                  NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                    NDP_OPT_ARO_STATE_SUCCESS); 
}

int sixlowpan_format_init_src_short_dst_long(ipv6_addr_t *eut_addr)
{
    net_if_eui64_t eut_eui64;

    memcpy(&eut_eui64, &eut_addr->uint8[8], 8);
    eut_eui64.uint8[0] ^= 0x02;

    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_SHORT);
    return sixlowpan_format_init() && (eut_addr == NULL ||
           ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_eui64, 8, 0,
                                  NDP_NCE_STATUS_REACHABLE,
                                  NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                    NDP_OPT_ARO_STATE_SUCCESS); 
}

int sixlowpan_format_ip_check(msg_t *msg, ipv6_addr_t *sender, char *data,
                              int data_len) {
    uint8_t success = 0;
    char sender_str[41];

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == IPV6_PACKET_RECEIVED) {
        if (sender && slplugtest_utils_check_sender((ipv6_hdr_t *)msg->content.ptr,
                                                    sender)) {
            success++;
        }
        else {
            FAILURE("Sender of received packet is not %s.\n",
                    inet_ntop(AF_INET6, sender, sender_str, IPV6_MAX_ADDR_STR_LEN));
        } 
        if (data && slplugtest_utils_check_echo_data((uint8_t *)msg->content.ptr, 
                                                     (uint8_t *)data, data_len)) {
            success++;
        }
        else {
            FAILURE("Received echo data is not as expected.\n");
        }
    }

    if (success > 0) {
        return success;
    }
    else {
        return -1;
    }
}

int sixlowpan_format_ip_both_from_long(msg_t *msg) {
    uint8_t success = 0;

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == IPV6_PACKET_RECEIVED) {
        if (!sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->srcaddr.uint8[8]))) {
            success++;
        }
        if (!sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->destaddr.uint8[8]))) {
            success++;
        }
    }

    if (success > 0) {
        return success;
    }
    else {
        return -1;
    }
}

int sixlowpan_format_ip_both_from_short(msg_t *msg) {
    uint8_t success = 0;

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == IPV6_PACKET_RECEIVED) {
        if (sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->srcaddr.uint8[8]))) {
            success++;
        }
        if (sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->destaddr.uint8[8]))) {
            success++;
        }
    }

    if (success > 0) {
        return success;
    }
    else {
        return -1;
    }
}

int sixlowpan_format_ip_src_from_long_dst_from_short(msg_t *msg) {
    uint8_t success = 0;

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == IPV6_PACKET_RECEIVED) {
        if (!sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->srcaddr.uint8[8]))) {
            success++;
        }
        if (sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->destaddr.uint8[8]))) {
            success++;
        }
    }

    if (success > 0) {
        return success;
    }
    else {
        return -1;
    }
}

int sixlowpan_format_ip_src_from_short_dst_from_long(msg_t *msg) {
    uint8_t success = 0;

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == IPV6_PACKET_RECEIVED) {
        if (sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->srcaddr.uint8[8]))) {
            success++;
        }
        if (!sixlowpan_lowpan_eui64_to_short_addr((net_if_eui64_t *)
                    &(((ipv6_hdr_t *)msg->content.ptr)->destaddr.uint8[8]))) {
            success++;
        }
    }

    if (success > 0) {
        return success;
    }
    else {
        return -1;
    }
}

int sixlowpan_format_check_uncompressed(msg_t *msg)
{
    uint8_t disp[] = {0x41};
    uint8_t disp_mask = 0xff;

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == LOWPAN_FRAME_RECEIVED) {
        if (slplugtest_utils_check_dispatch(
                    (sixlowpan_lowpan_frame_t *) msg->content.ptr, disp,
                    &disp_mask, 1)) {
            return 1;
        }
        else {
            FAILURE("Received dispatch is not %02x (01000001).\n", disp[0]);
        }
    }

    return -1;
}

int sixlowpan_format_check_fragment(msg_t *msg, uint8_t first)
{
    uint8_t disp[] = {0xc0, 0xe0};
    uint8_t disp_mask = 0xf8;

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == LOWPAN_FRAME_RECEIVED) {
        if (first && slplugtest_utils_check_dispatch(
                         (sixlowpan_lowpan_frame_t *) msg->content.ptr, &disp[0],
                         &disp_mask, 1)) {
            return 1;
        }
        if (!first && slplugtest_utils_check_dispatch(
                          (sixlowpan_lowpan_frame_t *) msg->content.ptr, &disp[1],
                          &disp_mask, 1)) {
            return 1;
        }
        else {
            if (first) {
                FAILURE("First received dispatch is not 11000xxx (0xc0).\n");
            }
            else {
                FAILURE("Following received dispatch is not 11100xxx (0xe0).\n");
            }
        }
    }

    return -1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST1) && defined(EUT1))
int sixlowpan_format01_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_long(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
#if 0
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_both_from_long(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }
#endif

    SUCCESS("TD_6LoWPAN_FORMAT_01 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST1) && defined(EUT2))
int sixlowpan_format01_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_format_init_long(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
#if 0
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_both_from_long(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }
#endif
    SUCCESS("TD_6LoWPAN_FORMAT_01 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST2) && defined(EUT1))
int sixlowpan_format02_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_short(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_both_from_short(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_02 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST2) && defined(EUT2))
int sixlowpan_format02_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_short(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        success += res;
        res = sixlowpan_format_ip_both_from_short(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_02 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST3) && defined(EUT1))
int sixlowpan_format03_eut1(char *eut2_str, char *data_tmplt)
{
    ipv6_addr_t eut2;
    msg_t msg;
    uint8_t success = 0;
    uint8_t first = 0; 
    char data[254];

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_format_init_short(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    if (data_tmplt == NULL) {
        ERROR("Data string not initialized\n");
    }
    
    slplugtest_utils_generate_data(data, data_tmplt, 253);

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 253);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 253);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_fragment(&msg, first);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
            first = 1;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_03 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST3) && defined(EUT2))
int sixlowpan_format03_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;
    uint8_t first = 0; 

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_format_init_short(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 253);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_fragment(&msg, first);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
            first = 1;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_03 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST4) && defined(EUT1))
int sixlowpan_format04_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;
    msg_t msg;
    uint8_t success = 0;
    uint8_t first = 0; 

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_format_init_short(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 1232);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 1232);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_fragment(&msg, first);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
            first = 1;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_04 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST4) && defined(EUT2))
int sixlowpan_format04_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;
    uint8_t first = 0; 

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_format_init_short(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 1232);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_fragment(&msg, first);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
            first = 1;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_04 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST5) && defined(EUT1))
int sixlowpan_format05_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t target, eut2;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    ipv6_addr_set_all_nodes_addr(&target);

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_short(NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&target, 1, 1, (uint8_t *) data, 4);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_05 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST5) && defined(EUT2))
int sixlowpan_format05_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_short(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_05 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST6) && defined(EUT1))
int sixlowpan_format06_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t target, eut2;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    ipv6_addr_set_all_nodes_addr(&target);

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_long(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&target, 1, 1, (uint8_t *) data, 4);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
#if 0
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

#endif
    SUCCESS("TD_6LoWPAN_FORMAT_06 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST6) && defined(EUT2))
int sixlowpan_format06_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_long(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
#if 0
    while (success < 3) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }
#endif

    SUCCESS("TD_6LoWPAN_FORMAT_06 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST7) && defined(EUT1))
int sixlowpan_format07_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_src_long_dst_short(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_src_from_short_dst_from_long(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_07 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST7) && defined(EUT2))
int sixlowpan_format07_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_src_short_dst_long(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_src_from_long_dst_from_short(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_07 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST8) && defined(EUT1))
int sixlowpan_format08_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    if (!sixlowpan_format_init_src_short_dst_long(&eut2)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    printf("Waiting for echo reply (seq = 1, id = 0x0001) from %s\n",
           eut2_str);
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut2, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_src_from_long_dst_from_short(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_08 [EUT1]\n");
    return 1;
}
#endif
 
#if defined(MODULE_SHELL) || (defined(FORMAT) && defined(TEST8) && defined(EUT2))
int sixlowpan_format08_eut2(char *eut1_str, char *data)
{
    ipv6_addr_t eut1;
    msg_t msg;
    uint8_t success = 0;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_format_init_src_long_dst_short(&eut1)) {
        ERROR("Interface initialization failed.\n");
    }

    if (data == NULL) {
        ERROR("Data string not initialized\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);
    while (success < 5) {
        int res = 0;

        msg_receive(&msg);
        res = sixlowpan_format_ip_check(&msg, &eut1, data, 4);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_ip_src_from_short_dst_from_long(&msg);

        if (res != 2 && res >= 0) {
            SILENT_FAILURE();
        }

        success += res;
        res = sixlowpan_format_check_uncompressed(&msg);

        if (!res) {
            SILENT_FAILURE();
        }
        else if (res > 0) {
            success++;
        }
    }

    SUCCESS("TD_6LoWPAN_FORMAT_08 [EUT2]\n");
    return 1;
}
#endif

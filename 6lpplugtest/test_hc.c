/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */
#include "ipv6.h"
#include "msg.h"
#include "net_if.h"
#include "sixlowpan.h"

#include "test_hc.h"
#include "test_utils.h"
#include "test_coap_ping.h"

#if defined(MODULE_SHELL) || defined(HC)
int sixlowpan_hc_init(uint8_t hoplimit)
{
    ipv6_addr_t tmp;
    char addr_str[IPV6_MAX_ADDR_STR_LEN];

    sixlowpan_lowpan_set_iphc_status(LOWPAN_IPHC_ENABLE);
    ipv6_set_default_hop_limit(hoplimit);
    ipv6_addr_set_link_local_prefix(&tmp);

#if 0
    if (net_if_set_channel(IF_ID, CHANNEL) < 0) {
        printf("Can not set channel.\n");
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

int sixlowpan_hc_router_init(uint8_t hoplimit, ipv6_addr_t *prefix)
{
    sixlowpan_lowpan_set_iphc_status(LOWPAN_IPHC_ENABLE);
    ipv6_set_default_hop_limit(hoplimit);

    if (net_if_set_channel(IF_ID, CHANNEL) < 0) {
        printf("Can not set channel.");
    }

    return sixlowpan_lowpan_init_adhoc_interface(IF_ID, prefix);
}


int sixlowpan_hc_init_long(uint8_t hoplimit, ipv6_addr_t *eut_addr,
                           ipv6_addr_t *prefix)
{
    net_if_eui64_t eut_eui64;

    memcpy(&eut_eui64, &eut_addr->uint8[8], 8);
    if (eut_eui64.uint32[0] != HTONL(0x000000ff) &&
        eut_eui64.uint16[2] != HTONS(0xfe00)) {
        eut_eui64.uint8[0] ^= 0x02;
    }

    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_LONG);

    if (prefix == NULL) {
        return sixlowpan_hc_init(hoplimit) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_eui64, 8, 0,
                                      NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }    
    else {
        return sixlowpan_hc_router_init(hoplimit, prefix) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_eui64, 8, 0,
                                      NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }
}

int sixlowpan_hc_init_short(uint8_t hoplimit, ipv6_addr_t *eut_addr,
                            ipv6_addr_t *prefix)
{
    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_SHORT);

    if (prefix == NULL) {
        return sixlowpan_hc_init(hoplimit) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_addr->uint16[7], 2,
                                      0, NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }    
    else {
        return sixlowpan_hc_router_init(hoplimit, prefix) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_addr->uint16[7], 2,
                                      0, NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }
}

int sixlowpan_hc_init_src_long_dst_short(uint8_t hoplimit, ipv6_addr_t *eut_addr,
                                         ipv6_addr_t *prefix)
{
    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_LONG);

    if (prefix == NULL) {
        return sixlowpan_hc_init(hoplimit) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_addr->uint16[7], 2,
                                      0, NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }    
    else {
        return sixlowpan_hc_router_init(hoplimit, prefix) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_addr->uint16[7], 2,
                                      0, NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }
}

int sixlowpan_hc_init_src_short_dst_long(uint8_t hoplimit, ipv6_addr_t *eut_addr,
                                         ipv6_addr_t *prefix)
{
    net_if_eui64_t eut_eui64;

    memcpy(&eut_eui64, &eut_addr->uint8[8], 8);
    eut_eui64.uint8[0] ^= 0x02;

    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_SHORT);

    if (prefix == NULL) {
        return sixlowpan_hc_init(hoplimit) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_eui64, 8, 0,
                                      NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }    
    else {
        return sixlowpan_hc_router_init(hoplimit, prefix) && (eut_addr == NULL ||
               ndp_neighbor_cache_add(IF_ID, eut_addr, &eut_eui64, 8, 0,
                                      NDP_NCE_STATUS_REACHABLE,
                                      NDP_NCE_TYPE_TENTATIVE, 0xffff) == 
                        NDP_OPT_ARO_STATE_SUCCESS); 
    }
}

#if defined(MODULE_SHELL) || defined(EUT2)
int sixlowpan_hc_check_iphc(msg_t *msg, uint8_t expected_tf_flag,
                            uint8_t expected_hl_flag,
                            uint8_t expected_addr_comp_flags)
{
    uint8_t disp[] = {0x60, 0x00};
    uint8_t disp_mask[] = {0xe0, 0x00};

    if (msg == NULL) {
        ERROR("Message not set\n");
    }

    if (msg->type == LOWPAN_FRAME_RECEIVED) {
        if (slplugtest_utils_check_dispatch(
                    (sixlowpan_lowpan_frame_t *) msg->content.ptr, disp,
                    disp_mask, 2)) {
            sixlowpan_lowpan_frame_t *frame = (sixlowpan_lowpan_frame_t *)msg->content.ptr;
            
            if (!(frame->data[0] & expected_tf_flag)) {
                printf("INFO: Either traffic class or flow label not compressed "
                       "as expected but this is only a feature\n");
            }
            if (!(frame->data[0] & expected_hl_flag)) {
                printf("INFO: Hop limit not compressed as expectded, but this "
                       "is only a feature\n");
            }
            if (!(frame->data[1] & expected_addr_comp_flags)) {
                printf("INFO: Source and destination address not compressed as "
                       "expected\n");
            }

            return 1;
        }
        else {
            FAILURE("Received dispatch is not %02x%02x (with certain flags).\n",
                    disp[0], disp[1]);
        }
    }

    return -1;
}
#endif

int sixlowpan_hc_check_udp_nhc(msg_t *msg, uint8_t flags, uint8_t mask) {
    sixlowpan_lowpan_frame_t *frame = (sixlowpan_lowpan_frame_t *)msg->content.ptr;
    uint8_t nhc_idx = 2;

    if (frame->length < nhc_idx) {
        return 0;
    }

    if (msg->type == LOWPAN_FRAME_RECEIVED) {
        if (frame->data[0] & 0x04) {
            return 0;
        }

        if (((frame->data[0] & 0x18) >> 3) == 0) {
            nhc_idx += 4;
        } 
        else if (((frame->data[0] & 0x18) >> 3) == 1) {
            nhc_idx += 3;
        } 
        else if (((frame->data[0] & 0x18) >> 3) == 2) {
            nhc_idx += 1;
        } 

        if (!(frame->data[0] & 0x03)) {
            nhc_idx += 1;
        }

        if (!(frame->data[1] & 0x80)) {
            nhc_idx += 1;
        }
        if (frame->data[1] & 0x40) {
            if (((frame->data[1] & 0x30) >> 4) == 0) {
                nhc_idx += 16;
            }
            if (((frame->data[1] & 0x30) >> 4) == 1) {
                nhc_idx += 8;
            }
            else if (((frame->data[1] & 0x30) >> 4) == 2) {
                nhc_idx += 2;
            }
        }
        else {
            if (((frame->data[1] & 0x30) >> 4) == 1) {
                nhc_idx += 8;
            }
            else if (((frame->data[1] & 0x30) >> 4) == 2) {
                nhc_idx += 2;
            }
        }

        if (frame->data[1] & 0x08 && frame->data[1] & 0x04) {
            if ((frame->data[1] & 0x03) == 0) {
                nhc_idx += 6;
            }
        }
        else if (frame->data[1] & 0x08 && !(frame->data[1] & 0x04)) {
            if ((frame->data[1] & 0x03) == 0) {
                nhc_idx += 16;
            }
            if ((frame->data[1] & 0x03) == 1) {
                nhc_idx += 6;
            }
            else if ((frame->data[1] & 0x03) == 2) {
                nhc_idx += 4;
            }
            else if ((frame->data[1] & 0x03) == 3) {
                nhc_idx += 1;
            }
        }
        else if (!(frame->data[1] & 0x08) && frame->data[1] & 0x04) {
            if ((frame->data[1] & 0x03) == 1) {
                nhc_idx += 8;
            }
            else if ((frame->data[1] & 0x03) == 2) {
                nhc_idx += 2;
            }
        }
        else {
            if ((frame->data[1] & 0x03) == 0) {
                nhc_idx += 16;
            }
            if ((frame->data[1] & 0x03) == 1) {
                nhc_idx += 8;
            }
            else if ((frame->data[1] & 0x03) == 2) {
                nhc_idx += 2;
            }
        }
    }

    return (frame->data[nhc_idx] & (0xf8 | mask)) == (0xf8 | flags);
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST1) && defined(EUT1))
int sixlowpan_hc01_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized or shorter than 4\n");
    }

    if (!sixlowpan_hc_init_long(64, &eut2, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_HC_01 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST1) && defined(EUT2))
int sixlowpan_hc01_eut2(char *eut1_str)
{
    ipv6_addr_t eut1;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_long(64, &eut1, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);

    msg_receive(&msg);

    if (sixlowpan_hc_check_iphc(&msg, 0x18, 0x2, 0x55) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_01 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST2) && defined(EUT1))
int sixlowpan_hc02_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized or shorter than 4\n");
    }

    if (!sixlowpan_hc_init_short(64, &eut2, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_HC_02 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST2) && defined(EUT2))
int sixlowpan_hc02_eut2(char *eut1_str)
{
    ipv6_addr_t eut1;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(64, &eut1, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);

    msg_receive(&msg);

    if (sixlowpan_hc_check_iphc(&msg, 0x18, 0x2, 0x55) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_02 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST3) && defined(EUT1))
int sixlowpan_hc03_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized or shorter than 4\n");
    }

    if (!sixlowpan_hc_init_long(63, &eut2, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_HC_03 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST3) && defined(EUT2))
int sixlowpan_hc03_eut2(char *eut1_str)
{
    ipv6_addr_t eut1;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_long(63, &eut1, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);

    msg_receive(&msg);

    if (sixlowpan_hc_check_iphc(&msg, 0x18, 0x00, 0x55) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_03 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST4) && defined(EUT1))
int sixlowpan_hc04_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized or shorter than 4\n");
    }

    if (!sixlowpan_hc_init_short(63, &eut2, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_HC_04 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST4) && defined(EUT2))
int sixlowpan_hc04_eut2(char *eut1_str)
{
    ipv6_addr_t eut1;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(63, &eut1, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);

    msg_receive(&msg);

    if (sixlowpan_hc_check_iphc(&msg, 0x18, 0x00, 0x55) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_04 [EUT2]\n");
    return 1;
}
#endif

#ifdef MODULE_LIBCOAP
#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST5) && defined(EUT1))
int sixlowpan_hc05_6lr(char *prefix_str, char *r_addr_str)
{
    ipv6_addr_t prefix, r_addr;
    int prefix_len;

    if (!slplugtest_utils_init_ll_eut_addr(&r_addr, r_addr_str)) {
        SILENT_ERROR();
    }

    if (!slplugtest_utils_init_prefix(&prefix, &prefix_len, prefix_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_long(255, &r_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_send_ping(5683, &r_addr, 5683);

    SUCCESS("TD_6LoWPAN_HC_05 [6LoWPAN router]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST5) && defined(EUT2))
int sixlowpan_hc05_host(char *host_addr_str)
{
    ipv6_addr_t host_addr;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&host_addr, host_addr_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(255, &host_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_run_server(5683);

    msg_receive(&msg);

    if (sixlowpan_hc_check_udp_nhc(&msg, 0x00, 0x0d) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_04 [6LoWPAN host]");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST6) && defined(EUT1))
int sixlowpan_hc06_6lr(char *prefix_str, char *r_addr_str)
{
    ipv6_addr_t prefix, r_addr;

    if (!slplugtest_utils_init_ll_eut_addr(&r_addr, r_addr_str)) {
        SILENT_ERROR();
    }

    if (!slplugtest_utils_init_ll_eut_addr(&prefix, prefix_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(255, &r_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_send_ping(5683, &r_addr, 5683);

    SUCCESS("TD_6LoWPAN_HC_05 [6LoWPAN router]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST6) && defined(EUT2))
int sixlowpan_hc06_host(char *host_addr_str)
{
    ipv6_addr_t host_addr;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&host_addr, host_addr_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(255, &host_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_run_server(5683);

    msg_receive(&msg);

    if (sixlowpan_hc_check_udp_nhc(&msg, 0x00, 0x0d) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_04 [6LoWPAN host]");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST7) && defined(EUT1))
int sixlowpan_hc07_6lr(char *prefix_str, char *r_addr_str)
{
    ipv6_addr_t prefix, r_addr;

    if (!slplugtest_utils_init_ll_eut_addr(&r_addr, r_addr_str)) {
        SILENT_ERROR();
    }

    if (!slplugtest_utils_init_ll_eut_addr(&prefix, prefix_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_long(255, &r_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_send_ping(61616, &r_addr, 61616);

    SUCCESS("TD_6LoWPAN_HC_05 [6LoWPAN router]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST7) && defined(EUT2))
int sixlowpan_hc07_host(char *host_addr_str)
{
    ipv6_addr_t host_addr;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&host_addr, host_addr_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(255, &host_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_run_server(61616);

    msg_receive(&msg);

    if (sixlowpan_hc_check_udp_nhc(&msg, 0x00, 0x0d) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_04 [6LoWPAN host]");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST8) && defined(EUT1))
int sixlowpan_hc08_6lr(char *prefix_str, char *r_addr_str)
{
    ipv6_addr_t prefix, r_addr;

    if (!slplugtest_utils_init_ll_eut_addr(&r_addr, r_addr_str)) {
        SILENT_ERROR();
    }

    if (!slplugtest_utils_init_ll_eut_addr(&prefix, prefix_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(255, &r_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_send_ping(61616, &r_addr, 61616);

    SUCCESS("TD_6LoWPAN_HC_05 [6LoWPAN router]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST8) && defined(EUT2))
int sixlowpan_hc08_host(char *host_addr_str)
{
    ipv6_addr_t host_addr;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&host_addr, host_addr_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_short(255, &host_addr, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    slpt_coap_run_server(61616);

    msg_receive(&msg);

    if (sixlowpan_hc_check_udp_nhc(&msg, 0x00, 0x0d) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_04 [6LoWPAN host]");
    return 1;
}
#endif
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST9) && defined(EUT1))
int sixlowpan_hc09_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized or shorter than 4\n");
    }

    if (!sixlowpan_hc_init_src_long_dst_short(64, &eut2, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_HC_09 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST9) && defined(EUT2))
int sixlowpan_hc09_eut2(char *eut1_str)
{
    ipv6_addr_t eut1;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_src_short_dst_long(64, &eut1, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);

    msg_receive(&msg);

    if (sixlowpan_hc_check_iphc(&msg, 0x18, 0x2, 0x55) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_09 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST10) && defined(EUT1))
int sixlowpan_hc10_eut1(char *eut2_str, char *data)
{
    ipv6_addr_t eut2;

    if (!slplugtest_utils_init_ll_eut_addr(&eut2, eut2_str)) {
        SILENT_ERROR();
    }

    if (data == NULL) {
        ERROR("Data string not initialized or shorter than 4\n");
    }

    if (!sixlowpan_hc_init_src_short_dst_long(64, &eut2, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    icmpv6_send_echo_request(&eut2, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_HC_10 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(HC) && defined(TEST10) && defined(EUT2))
int sixlowpan_hc10_eut2(char *eut1_str)
{
    ipv6_addr_t eut1;
    msg_t msg;

    if (!slplugtest_utils_init_ll_eut_addr(&eut1, eut1_str)) {
        SILENT_ERROR();
    }

    if (!sixlowpan_hc_init_src_long_dst_short(64, &eut1, NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    printf("Waiting for echo request from %s\n", eut1_str);

    msg_receive(&msg);

    if (sixlowpan_hc_check_iphc(&msg, 0x18, 0x2, 0x55) < 0) {
        SILENT_FAILURE();
    }

    SUCCESS("TD_6LoWPAN_HC_10 [EUT2]\n");
    return 1;
}
#endif

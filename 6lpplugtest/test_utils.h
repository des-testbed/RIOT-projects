/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @file    test_utils.h
 * @brief   Common 6LoWPAN Plugtest functions. 
 * @author  Martine Lenders <mlenders@inf.fu-berlin.de>
 */
#ifndef _6LPPLUGTEST_TEST_UTILS_H 
#define _6LPPLUGTEST_TEST_UTILS_H
#include <stdio.h>
#include <stdint.h>

#include "ipv6.h"
#include "sixlowpan.h"

#define IF_ID (0)

#define ERROR(...) fprintf(stderr, "ERROR: " __VA_ARGS__); return 0
#define SILENT_ERROR() return 0
#define FAILURE(...) printf("FAILURE: "__VA_ARGS__) // ; return 0
#define SILENT_FAILURE() printf("DEBUG:FAILURE: %s:%d\n", __FILE__, __LINE__) // ; return 0
#define SUCCESS(...) printf("SUCCESS: "__VA_ARGS__)

uint8_t slplugtest_utils_initialize_queue(void);
void slplugtest_utils_generate_data(char *data_out, char *data_in, size_t data_len);
uint8_t slplugtest_utils_init_ll_eut_addr(ipv6_addr_t *eut_addr, char *eut_addr_str);
uint8_t slplugtest_utils_init_eut_addr(ipv6_addr_t *eut_addr, char *eut_addr_str);
uint8_t slplugtest_utils_init_prefix(ipv6_addr_t *prefix, int *prefix_len,
                                     char *prefix_str);
uint8_t slplugtest_utils_register_to_lowpan(void);
uint8_t slplugtest_utils_register_to_ipv6(void);
uint8_t slplugtest_utils_check_dispatch(sixlowpan_lowpan_frame_t *data, 
                                        uint8_t *disp, uint8_t *disp_mask,
                                        uint8_t disp_len);
uint8_t slplugtest_utils_check_sender(ipv6_hdr_t *header, ipv6_addr_t *addr);
uint8_t slplugtest_utils_check_echo_data(uint8_t *packet, uint8_t *data,
                                         uint8_t data_len);
void slplugtest_utils_str_to_eui64(net_if_eui64_t *eui64, char *eui64_str);
#endif /* _6LPPLUGTEST_TEST_UTILS_H */

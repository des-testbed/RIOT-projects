/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @file    test_nd.h
 * @brief   6LoWPAN neighbor discovery Plugtests. 
 */
#ifndef _6LPPLUGTEST_TEST_ND_H
#define _6LPPLUGTEST_TEST_ND_H

#include "ipv6.h"

/**
 * @brief   Check that a host is able to register its global IPv6 address in 
 *          Host-6LR configuration (EUI-64); Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-10.2">
 *          RFC 6775, section 10.2
 *      </a>
 *
 * @pre 6LR is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd01_6lr()).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd01_host(void);

/**
 * @brief   Check that a host is able to register its global IPv6 address in 
 *          Host-6LR configuration (EUI-64); 6LoWPAN router behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-10.2">
 *          RFC 6775, section 10.2
 *      </a>
 *
 * @param[in] prefix    The prefix to use in PIO of this 6LoWPAN router in
 *                      string representation.
 * @param[in] host_addr IPv6 link-local address of the host in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd01_6lr(char *prefix, char *host_addr, char* data);

/**
 * @brief   Check that a host is able to register its global IPv6 address in 
 *          Host-6LR configuration (16-bit); Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-10.2">
 *          RFC 6775, section 10.2
 *      </a>
 *
 * @pre 6LR is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd02_6lr()).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd02_host(void);

/**
 * @brief   Check that a host is able to register its global IPv6 address in 
 *          Host-6LR configuration (16-bit); 6LoWPAN router behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-10.2">
 *          RFC 6775, section 10.2
 *      </a>
 *
 * @param[in] prefix    The prefix to use in PIO of this 6LoWPAN router in
 *                      string representation.
 * @param[in] host_addr IPv6 link-local address of the host in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd02_6lr(char *prefix, char *host_addr, char* data);

/**
 * @brief   Check Host NUD behavior in Host-6LR configuration; Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.5">
 *          RFC 6775, section 5.5
 *      </a>
 *
 * @pre 6LR is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd03_6lr()).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd03_host(void);

/**
 * @brief   Check Host NUD behavior in Host-6LR configuration; 6LoWPAN router 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.5">
 *          RFC 6775, section 5.5
 *      </a>
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd03_6lr(void);

/**
 * @brief   Check Host NUD behavior (ICMP version) in Host-6LR configuration;
 *          Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.5">
 *          RFC 6775, section 5.5
 *      </a>
 *
 * @pre Host is configured to use EUI-64.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd04_host(void);

/**
 * @brief   Check Host NUD behavior (ICMP version) in Host-6LR configuration; 
 *          6LoWPAN router behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.5">
 *          RFC 6775, section 5.5
 *      </a>
 *
 * @pre Host is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd04_host()).
 *
 * @param[in] prefix    The prefix to use in PIO of this 6LoWPAN router in
 *                      string representation.
 * @param[in] host_addr IPv6 link-local address of the host in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd04_6lr(char *prefix, char *host_addr, char* data);

/**
 * @brief   Check Host NUD behavior (UDP version) in Host-6LR configuration;
 *          Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.5">
 *          RFC 6775, section 5.5
 *      </a>
 *
 * @pre Host is configured to use EUI-64.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd05_host(void);

/**
 * @brief   Check Host NUD behavior (UDP version) in Host-6LR configuration; 
 *          6LoWPAN router behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.5">
 *          RFC 6775, section 5.5
 *      </a>
 *
 * @pre Host is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd05_host()).
 *
 * @param[in] prefix    The prefix to use in PIO of this 6LoWPAN router in
 *                      string representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd05_6lr(char *prefix);

/**
 * @brief   Check host behavior under multiple prefixes (EUI-64) in Host-6LR
 *          configuration; Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-3.1">
 *          RFC 6775, section 3.1
 *      </a>
 *
 * @pre Host is configured to use EUI-64.
 * @pre 6LR is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd06_6lr()).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd06_host(void);

/**
 * @brief   Check host behavior under multiple prefixes (EUI-64) in Host-6LR
 *          configuration; 6LoWPAN router behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-3.1">
 *          RFC 6775, section 3.1
 *      </a>
 *
 * @pre prefixes is not NULL
 * @pre prefixes contains more than one address
 * @pre prefix_num > 1
 *
 * @param[in] prefix_list_len   Length of prefix list
 * @param[in] prefix_list       Prefixes this router should send in its PIO 
 *                              as string representation.
 * @param[in] host_addr         IPv6 link-local address of the host in string
 *                              representation.
 * @param[in] data              Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd06_6lr(int prefix_list_len, char **prefix_list, char *host_addr,
                       char* data);

/**
 * @brief   Check host behavior under multiple prefixes (16-bit) in Host-6LR
 *          configuration; Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-3.1">
 *          RFC 6775, section 3.1
 *      </a>
 *
 * @pre 6LR is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd07_6lr()).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd07_host(void);

/**
 * @brief   Check host behavior under multiple prefixes (16-bit) in Host-6LR
 *          configuration; 6LoWPAN router behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-3.1">
 *          RFC 6775, section 3.1
 *      </a>
 *
 * @param[in] prefix_list_len   Length of prefix list
 * @param[in] prefix_list       Prefixes this router should send in its PIO 
 *                              as string representation.
 * @param[in] host_addr         IPv6 link-local address of the host in string
 *                              representation.
 * @param[in] data              Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd07_6lr(int prefix_list_len, char **prefix_list, char *host_addr,
                       char* data);

#endif /* _6LPPLUGTEST_TEST_ND_H */

/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @file    test_hc.h
 * @brief   6LoWPAN header compression Plugtests. 
 */
#ifndef _6LPPLUGTEST_TEST_HC_H 
#define _6LPPLUGTEST_TEST_HC_H

#include <ipv6.h>

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 link-local, hop limit=64); EUT1 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc01_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc01_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 link-local, hop limit=64); EUT2 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc01_eut2(char *eut1_addr);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit link-local, hop limit=64); EUT1 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc02_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc02_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit link-local, hop limit=64); EUT2 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT is configured to use 16-bit short address.
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc02_eut2(char *eut1_addr);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 link-local, hop limit=63); EUT1 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc03_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc03_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 link-local, hop limit=63); EUT2 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc03_eut2(char *eut1_addr);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit link-local, hop limit=63); EUT1 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc02_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc04_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit link-local, hop limit=63); EUT2 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc04_eut2(char *eut1_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (EUI-64 link-local, server port=5683); Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to use EUI-64.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc05_host(char *r_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (EUI-64 link-local, server port=5683); 6LoWPAN router
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc05_host()).
 *
 * @param[in]   host_addr   IPv6 link-local address of the host in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc05_6lr(char *prefix, char *host_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (16-bit link-local, server port=5683); Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to use 16-bit short address.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc06_host(char *r_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (16-bit link-local, server port=5683); 6LoWPAN router
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc06_host()).
 *
 * @param[in]   host_addr   IPv6 link-local address of the host in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc06_6lr(char *prefix, char *host_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (EUI-64 link-local, server port=5683); Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to use EUI-64.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc07_host(char *r_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (EUI-64 link-local, server port=61616); 6LoWPAN router
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc07_host()).
 *
 * @param[in]   host_addr   IPv6 link-local address of the host in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc07_6lr(char *prefix, char *host_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (16-bit link-local, server port=61616); Host behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc08_host(char *r_addr);

/**
 * @brief   Check that EUTs correctly handle compressed UDP packets in Node-Node
 *          configuration (16-bit link-local, server port=61616); 6LoWPAN router
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 4.3
 *      </a>
 *
 * @pre Host is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc08_host()).
 *
 * @param[in]   host_addr   IPv6 link-local address of the host in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc08_6lr(char *prefix, char *host_addr);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 TO 16-bit link-local, hop limit=64); 
 *          EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc09_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc09_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 TO 16-bit link-local, hop limit=64); 
 *          EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc09_eut2(char *eut1_addr);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit to EUI-64 link-local, hop limit=64); 
 *          EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_hc10_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc10_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle compressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit to EUI-64 link-local, hop limit=64); 
 *          EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3">
 *          RFC 6282, section 3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_hc10_eut2(char *eut1_addr);

#endif /* _6LPPLUGTEST_TEST_HC_H */

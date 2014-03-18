/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @file    test_format.h
 * @brief   6LoWPAN format Plugtests. 
 */
#ifndef _6LPPLUGTEST_TEST_FORMAT_H 
#define _6LPPLUGTEST_TEST_FORMAT_H
#include <stdint.h>

#include "ipv6.h"

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 link-local); EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format01_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format01_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 link-local); EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format01_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit link-local); EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format02_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format02_eut1(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit link-local); EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format02_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN fragmented 
 *          packets in Node-Node configuration; EUT1 behavior.
 * 
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.3">
 *          RFC 4944, section 5.3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format03_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 253).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format03_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN fragmented 
 *          packets in Node-Node configuration; EUT2 behavior.
 * 
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.3">
 *          RFC 4944, section 5.3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 253).
 *
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format03_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle maximum size uncompressed 6LoWPAN
 *          fragmented packets in Node-Node configuration; EUT1 behavior.
 * 
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.3">
 *          RFC 4944, section 5.3
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format04_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 1232).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format04_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle maximum size uncompressed 6LoWPAN
 *          fragmented packets in Node-Node configuration; EUT2 behavior.
 * 
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.3">
 *          RFC 4944, section 5.3
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 1232).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format04_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN multicast to
 *          all-nodes (16-bit link-local) in Node-Node configuration; EUT1
 *          behavior
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format05_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format05_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN multicast to
 *          all-nodes (16-bit link-local) in Node-Node configuration; EUT2
 *          behavior
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format05_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN multicast to
 *          all-nodes (EUI-64 link-local) in Node-Node configuration; EUT1
 *          behavior
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format06_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format06_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN multicast to
 *          all-nodes (EUI-64 link-local) in Node-Node configuration; EUT2
 *          behavior
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format06_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 to 16-bit link-local); EUT1 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format07_eut2()).
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format07_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format07_eut1(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (EUI-64 to 16-bit link-local); EUT2 
 *          behavior. 
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format07_eut2(char *eut1_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit to EUI-64 link-local); EUT1 
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_format08_eut2()).
 *
 * @param[in]   eut2_addr   IPv6 link-local address of EUT2 in string
 *                          representation.
 * @param[in]   data        Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format08_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs correctly handle uncompressed 6LoWPAN packets in 
 *          Node-Node configuration (16-bit to EUI-64 link-local); EUT2
 *          behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-5.1">
 *          RFC 4944, section 5.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc4944#section-8">
 *          RFC 4944, section 8
 *      </a>
 *
 * @param[in]   eut1_addr   IPv6 link-local address of EUT1 in string
 *                          representation.
 * @param[in]   data        Test data to expect (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_format08_eut2(char *eut1_addr, char *data);

#endif /* _6LPPLUGTEST_TEST_FORMAT_H */

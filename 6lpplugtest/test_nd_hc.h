/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @file    test_nd_hc.h
 * @brief   6LoWPAN neighbor discovery + header compression Plugtests. 
 */
#ifndef _6LPPLUGTEST_TEST_ND_HC_H
#define _6LPPLUGTEST_TEST_ND_HC_H

#include "ipv6.h"

/**
 * Run 6LoWPAN router (initialized with sixlowpan_nd_hc_6lr()) not as an EUT
 * simultanously if set. 
 */
#define SLPT_6LR_FLAG_STANDALONE 0x1

/**
 * Run 6LoWPAN router (initialized with sixlowpan_nd_hc_6lr()) with global
 * IPv6 prefix as context = 0 if set. 
 */
#define SLPT_6LR_FLAG_CONTEXT0 0x2

/**
 * Run 6LoWPAN router (initialized with sixlowpan_nd_hc_6lr()) with EUI-64 
 * if set or with 16-bit short address otherwise. 
 */
#define SLPT_6LR_FLAG_64BIT 0x4

/**
 * @brief   Assures that this node will be initialized as 6LoWPAN router
 *          in the tests of this scope. 
 *
 * @param[in]   prefix the prefix to put into context
 * @param[in]   flags  configuration flags for the router (prefixed with
 *                     SLPT_6LR_FLAG_).
 */
void sixlowpan_nd_hc_6lr(char *prefix, uint8_t flags);

/**
 * @brief   Check that EUTs make use of context = 0 in Host-6LR configuration 
 *          (EUI-64); EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd_hc01_eut2()).
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc01_eut1() or sixlowpan_nd_hc01_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use EUI-64 (On RIOT: run sixlowpan_nd_hc_6lr() 
 *      with flag 6LPPLUGTEST_6LR_FLAG_64BIT set).
 * @pre The PAN's global/64-prefix is stored as context = 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 set).
 *
 * @param[in] eut2_addr IPv6 global/64-prefixed address of EUT2 in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc01_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs make use of context = 0 in Host-6LR configuration 
 *          (EUI-64); EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc01_eut1() or sixlowpan_nd_hc01_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use EUI-64 (On RIOT: run sixlowpan_nd_hc_6lr() 
 *      with flag 6LPPLUGTEST_6LR_FLAG_64BIT set).
 * @pre The PAN's global/64-prefix is stored as context = 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 set).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc01_eut2(void);

/**
 * @brief   Check that EUTs make use of context = 0 in Host-6LR configuration 
 *          (16-bit); EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd_hc02_eut2()).
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc02_eut1() or sixlowpan_nd_hc02_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use 16-bit short address (On RIOT: 
 *      run sixlowpan_nd_hc_6lr() with flag 6LPPLUGTEST_6LR_FLAG_64BIT unset).
 * @pre The PAN's global/16-prefix is stored as context = 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 set).
 *
 * @param[in] eut2_addr IPv6 global/64-prefixed address of EUT2 in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc02_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs make use of context = 0 in Host-6LR configuration 
 *          (16-bit); EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.1">
 *          RFC 6282, section 3.1.1
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc02_eut1() or sixlowpan_nd_hc02_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use 16-bit short address (On RIOT: 
 *      run sixlowpan_nd_hc_6lr() with flag 6LPPLUGTEST_6LR_FLAG_64BIT unset).
 * @pre The PAN's global/16-prefix is stored as context = 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 set).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc02_eut2(void);

/**
 * @brief   Check that EUTs make use of context != 0 in Host-6LR configuration 
 *          (EUI-64); EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.2">
 *          RFC 6282, section 3.1.2
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd_hc03_eut2()).
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc03_eut1() or sixlowpan_nd_hc03_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use EUI-64 (On RIOT: run sixlowpan_nd_hc_6lr() 
 *      with flag 6LPPLUGTEST_6LR_FLAG_64BIT set).
 * @pre The PAN's global/64-prefix is stored as context != 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 unset).
 *
 * @param[in] eut2_addr IPv6 global/64-prefixed address of EUT2 in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc03_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs make use of context != 0 in Host-6LR configuration 
 *          (EUI-64); EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.2">
 *          RFC 6282, section 3.1.2
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc03_eut1() or sixlowpan_nd_hc03_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use EUI-64 (On RIOT: run sixlowpan_nd_hc_6lr() 
 *      with flag 6LPPLUGTEST_6LR_FLAG_64BIT set).
 * @pre The PAN's global/64-prefix is stored as context != 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 unset).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc03_eut2(void);

/**
 * @brief   Check that EUTs make use of context != 0 in Host-6LR configuration 
 *          (16-bit); EUT1 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.2">
 *          RFC 6282, section 3.1.2
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre EUT2 is configured to react to this test (On RIOT: run 
 *      sixlowpan_nd_hc04_eut2()).
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc04_eut1() or sixlowpan_nd_hc04_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use 16-bit short address (On RIOT: 
 *      run sixlowpan_nd_hc_6lr() with flag 6LPPLUGTEST_6LR_FLAG_64BIT unset).
 * @pre The PAN's global/16-prefix is stored as context != 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 unset).
 *
 * @param[in] eut2_addr IPv6 global/64-prefixed address of EUT2 in string
 *                      representation.
 * @param[in] data      Test data to send (min length 4).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc04_eut1(char *eut2_addr, char *data);

/**
 * @brief   Check that EUTs make use of context != 0 in Host-6LR configuration 
 *          (16-bit); EUT2 behavior.
 *
 * @see <a href="http://tools.ietf.org/html/rfc6282#section-3.1.2">
 *          RFC 6282, section 3.1.2
 *      </a>
 * @see <a href="http://tools.ietf.org/html/rfc6775#section-5.4">
 *          RFC 6775, section 5.4
 *      </a>
 *
 * @pre An 6LoWPAN router (6LR) is running in the network (On RIOT: run 
 *      sixlowpan_nd_hc_6lr() on one of the EUTs before 
 *      sixlowpan_nd_hc04_eut1() or sixlowpan_nd_hc04_eut2() respectively or
 *      standalone).
 * @pre 6LR is configured to use 16-bit short address (On RIOT: 
 *      run sixlowpan_nd_hc_6lr() with flag 6LPPLUGTEST_6LR_FLAG_64BIT unset).
 * @pre The PAN's global/16-prefix is stored as context != 0 in the 6LoWPAN
 *      router's context table. (On RIOT: run sixlowpan_nd_hc_6lr() with 
 *      flag 6LPPLUGTEST_6LR_FLAG_CONTEXT0 unset).
 *
 * @return  1 if test is successful, 0 otherwise
 */
int sixlowpan_nd_hc04_eut2(void);

#endif /* _6LPPLUGTEST_TEST_ND_HC_H */

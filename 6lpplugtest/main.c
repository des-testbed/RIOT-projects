/*
 * Copyright (C) 2013-14 Martin Lenders <mlenders@inf.fu-berlin.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */
#include <stdio.h>

#include "sixlowpan.h"

#ifdef MODULE_SHELL
#include "test_shell.h"
#elif defined(FORMAT)
#include "test_format.h"
#elif defined(HC)
#include "test_hc.h"
#elif defined(ND)
#include "test_nd.h"
#elif defined(ND_HC)
#include "test_nd_hc.h"
#else
#error "Define one of these sections: FORMAT, HC, ND, ND_HC or use shell module.\n"
#endif

#include "test_utils.h"

int main(void)
{
    printf("6LoWPAN Plugtest\n");

    if (!slplugtest_utils_initialize_queue()) {
        ERROR("Could not initialize queue.\n");
        return 1;
    }

    if (!slplugtest_utils_register_to_lowpan()) {
        ERROR("Could not register to 6LoWPAN thread.\n");
        return 1;
    }

    if (!slplugtest_utils_register_to_ipv6()) {
        ERROR("Could not register to IPv6 thread.\n");
        return 1;
    }

#ifdef MODULE_SHELL
    sixlpplugtest_shell_init();

/* ifdef for format tests */
#elif defined(FORMAT) && defined(TEST1) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format01_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST1) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format01_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST2) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format02_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST2) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format02_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST3) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format03_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST3) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format03_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST4) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format04_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST4) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format04_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST5) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format05_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST5) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format05_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST6) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format06_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST6) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format06_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST7) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format07_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST7) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format07_eut2(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST8) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format08_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(FORMAT) && defined(TEST8) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_format08_eut2(DEST, DATA)) {
        return 1;
    }

/* ifdef for header compression tests */
#elif defined(HC) && defined(TEST1) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_hc01_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(HC) && defined(TEST1) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc01_eut2(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST2) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_hc02_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(HC) && defined(TEST2) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc02_eut2(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST3) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_hc03_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(HC) && defined(TEST3) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc03_eut2(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST4) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_hc04_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(HC) && defined(TEST4) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc04_eut2(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST5) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef IPPREFIX
#error "Please define a subnet prefix of length 64 with the IPPREFIX macro"
#endif
    if (!sixlowpan_hc05_6lr(IPPREFIX, DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST5) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc05_host(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST6) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef IPPREFIX
#error "Please define a subnet prefix of length 64 with the IPPREFIX macro"
#endif
    if (!sixlowpan_hc06_6lr(IPPREFIX, DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST6) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc06_host(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST7) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef IPPREFIX
#error "Please define a subnet prefix of length 64 with the IPPREFIX macro"
#endif
    if (!sixlowpan_hc07_6lr(IPPREFIX, DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST7) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc07_host(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST8) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef IPPREFIX
#error "Please define a subnet prefix of length 64 with the IPPREFIX macro"
#endif
    if (!sixlowpan_hc08_6lr(IPPREFIX, DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST8) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc08_host(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST9) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_hc09_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(HC) && defined(TEST9) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc09_eut2(DEST)) {
        return 1;
    }
#elif defined(HC) && defined(TEST10) && defined(EUT1)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_hc10_eut1(DEST, DATA)) {
        return 1;
    }
#elif defined(HC) && defined(TEST10) && defined(EUT2)
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
    if (!sixlowpan_hc10_eut2(DEST)) {
        return 1;
    }

/* ifdef for neighbor discovery tests */
#elif defined(ND) && defined(TEST1) && defined(EUT1)
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd01_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST1) && defined(EUT2)
#ifndef IPPREFIX
#error "Please define a test prefix via the IPPREFIX macro"
#endif
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd01_6lr(IPPREFIX, DEST, DATA)) {
        return 1;
    }
#elif defined(ND) && defined(TEST2) && defined(EUT1)
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd02_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST2) && defined(EUT2)
#ifndef IPPREFIX
#error "Please define a test prefix via the IPPREFIX macro"
#endif
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd02_6lr(IPPREFIX, DEST, DATA)) {
        return 1;
    }
#elif defined(ND) && defined(TEST3) && defined(EUT1)
    if (!sixlowpan_nd03_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST3) && defined(EUT2)
    if (!sixlowpan_nd03_6lr()) {
        return 1;
    }
#elif defined(ND) && defined(TEST4) && defined(EUT1)
#ifndef IPPREFIX
#error "Please define a test prefix via the IPPREFIX macro"
#endif
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd04_6lr(IPPREFIX, DEST, DATA)) {
        return 1;
    }
#elif defined(ND) && defined(TEST4) && defined(EUT2)
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd04_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST5) && defined(EUT1)
#ifndef IPPREFIX
#error "Please define a test prefix via the IPPREFIX macro"
#endif
    if (!sixlowpan_nd05_6lr(IPPREFIX)) {
        return 1;
    }
#elif defined(ND) && defined(TEST5) && defined(EUT2)
    if (!sixlowpan_nd05_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST6) && defined(EUT1)
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd06_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST6) && defined(EUT2)
#ifndef IPPREFIX
#error "Please define a test prefix via the IPPREFIX macro"
#endif
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
#ifndef IPPREFIX_LEN
#error "Please define the length of the prefix list via the IPPREFIX_LEN macro"
#endif
#if IPPREFIX_LEN < 2
#error "You need more than one prefix"
#endif
    char ipprefixes[strlen(IPPREFIX)];
    char *ipprefixes_list[IPPREFIX_LEN];
    int j = 0;
    
    memcpy(ipprefixes, IPPREFIX, strlen(IPPREFIX));
    ipprefixes_list[j++] = &ipprefixes[0]; 
    for (unsigned int i = 0; i < strlen(IPPREFIX) || j < IPPREFIX_LEN + 1; i++) {
        if (ipprefixes[i] == ' ') {
            ipprefixes[i] = '\0';
            ipprefixes_list[j++] = &ipprefixes[i+1];
        }
    } 

    if (!sixlowpan_nd06_6lr(IPPREFIX_LEN, ipprefixes_list, DEST, DATA)) {
        return 1;
    }
#elif defined(ND) && defined(TEST7) && defined(EUT1)
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
    if (!sixlowpan_nd07_host()) {
        return 1;
    }
#elif defined(ND) && defined(TEST7) && defined(EUT2)
#ifndef IPPREFIX
#error "Please define a test prefix via the IPPREFIX macro"
#endif
#ifndef DEST
#error "Please define a test destination via the DEST macro"
#endif
#ifndef DATA
#error "Please define test data with the DATA macro"
#endif
#ifndef IPPREFIX_LEN
#error "Please define the length of the prefix list via the IPPREFIX_LEN macro"
#endif
#if IPPREFIX_LEN < 2
#error "You need more than one prefix"
#endif
    char ipprefixes[strlen(IPPREFIX)];
    char *ipprefixes_list[IPPREFIX_LEN];
    int j = 0;
    
    memcpy(ipprefixes, IPPREFIX, strlen(IPPREFIX));
    ipprefixes_list[j++] = &ipprefixes[0]; 
    for (unsigned int i = 0; i < strlen(IPPREFIX) || j < IPPREFIX_LEN + 1; i++) {
        if (ipprefixes[i] == ' ') {
            ipprefixes[i] = '\0';
            ipprefixes_list[j++] = &ipprefixes[i+1];
        }
    } 

    if (!sixlowpan_nd07_6lr(IPPREFIX_LEN, ipprefixes_list, DEST, DATA)) {
        return 1;
    }
#elif (defined(FORMAT) || defined(HC) || defined(ND) || defined(ND_HC)) && \
      (defined(EUT1) || defined(EUT2))
#error "Please define a valid test TEST<n>\n"
#elif (defined(FORMAT) || defined(HC) || defined(ND) || defined(ND_HC)) && \
      !(defined(EUT1) || defined(EUT2))
#error "Please define which EUT you want to use: valid values are EUT1 or EUT2\n"
#endif
    while(1);
    return 0;
}



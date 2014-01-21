/*
 * Copyright (C) 2013 Martin Lenders <mlenders@inf.fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>
#include <string.h>

#include "transceiver.h"
#include "cc2420.h"

int test_wrong_set_channel(uint16_t channel)
{
    if (cc2420_set_channel(channel) != -1) {
        printf("Channel %d should yield error -1.\n", channel);
        return 0;
    }
    return 1;
}

int test_right_set_channel(void)
{
    uint16_t channel = cc2420_get_channel();

    if (channel == 26) {
        channel = 11;
    }
    else {
        channel++;
    }

    if (cc2420_set_channel(channel) == -1) {
        printf("Channel %d should not yield error -1.\n", channel);
        return 0;
    }
    return 1;
}


int test_set_channel(void)
{
    uint16_t channel = 0;

    if (!test_wrong_set_channel(channel)) {
        return 0;
    }

    channel = 0xffff;

    if (!test_wrong_set_channel(channel)) {
        return 0;
    }

    channel = 0xfffe;

    if (!test_wrong_set_channel(channel)) {
        return 0;
    }

    if (!test_right_set_channel()) {
        return 0;
    }

    return 1;
}

int test_get_channel(void)
{
    uint16_t asserted_channel = cc2420_get_channel();
    uint16_t got_channel;
    
    asserted_channel += 1;
    
    if (asserted_channel > 26) {
        asserted_channel = 11;
    } 
    
    if (!test_right_set_channel()) {
        return 0;
    }

    if (asserted_channel != (got_channel = cc2420_get_channel())) {
        printf("%d != %d\n", asserted_channel, got_channel);
        return 0;
    }

    return 1;
}

int test_get_set_address(void)
{
    uint16_t addr = 0x0000, new_addr;

    new_addr = cc2420_set_address(addr);

    if (new_addr != addr) {
        printf("new_addr [%d] != addr [%d] after set_address\n", new_addr, addr);
        return 0;
    }

    new_addr = cc2420_get_address();

    if (new_addr != addr) {
        printf("new_addr [%d] != addr [%d] after get_address\n", new_addr, addr);
        return 0;
    }

    addr = 0xffff;
    new_addr = cc2420_set_address(addr);

    if (new_addr != addr) {
        printf("new_addr [%d] != addr [%d] after set_address\n", new_addr, addr);
        return 0;
    }

    new_addr = cc2420_get_address();

    if (new_addr != addr) {
        printf("new_addr [%d] != addr [%d] after get_address\n", new_addr, addr);
        return 0;
    }

    addr = 0x0004; /* randomly chosen by fair dice roll ;-) */
    new_addr = cc2420_set_address(addr);

    if (new_addr != addr) {
        printf("new_addr [%d] != addr [%d] after set_address\n", new_addr, addr);
        return 0;
    }

    new_addr = cc2420_get_address();

    if (new_addr != addr) {
        printf("new_addr [%d] != addr [%d] after get_address\n", new_addr, addr);
        return 0;
    }

    return 1;
}

int test_get_set_address_long(void)
{
    uint64_t addr = 0x0000000000000000, new_addr;

    new_addr = cc2420_set_address(addr);

    if (new_addr != addr) {
        printf("new_addr [%" PRIu64 "] != addr [%" PRIu64 "] after set_address\n", new_addr, addr);
        return 0;
    }

    new_addr = cc2420_get_address();

    if (new_addr != addr) {
        printf("new_addr [%" PRIu64 "] != addr [%" PRIu64 "] after get_address\n", new_addr, addr);
        return 0;
    }

    addr = 0xffffffffffffffff;
    new_addr = cc2420_set_address(addr);

    if (new_addr != addr) {
        printf("new_addr [%" PRIu64 "] != addr [%" PRIu64 "] after set_address\n", new_addr, addr);
        return 0;
    }

    new_addr = cc2420_get_address();

    if (new_addr != addr) {
        printf("new_addr [%" PRIu64 "] != addr [%" PRIu64 "] after get_address\n", new_addr, addr);
        return 0;
    }

    addr = 0x0000000002bb3f52; /* randomly chosen by fair dice roll ;-) */
    new_addr = cc2420_set_address(addr);

    if (new_addr != addr) {
        printf("new_addr [%" PRIu64 "] != addr [%" PRIu64 "] after set_address\n", new_addr, addr);
        return 0;
    }

    new_addr = cc2420_get_address();

    if (new_addr != addr) {
        printf("new_addr [%" PRIu64 "] != addr [%" PRIu64 "] after get_address\n", new_addr, addr);
        return 0;
    }

    return 1;
}

int test_get_set_pan(void)
{
    uint16_t pan = 0x0000, new_pan;

    new_pan = cc2420_set_address(pan);

    if (new_pan != pan) {
        printf("new_pan [%d] != pan [%d] after set_address\n", new_pan, pan);
        return 0;
    }

    new_pan = cc2420_get_address();

    if (new_pan != pan) {
        printf("new_pan [%d] != pan [%d] after get_address\n", new_pan, pan);
        return 0;
    }

    pan = 0xffff;
    new_pan = cc2420_set_address(pan);

    if (new_pan != pan) {
        printf("new_pan [%d] != pan [%d] after set_address\n", new_pan, pan);
        return 0;
    }

    new_pan = cc2420_get_address();

    if (new_pan != pan) {
        printf("new_pan [%d] != pan [%d] after get_address\n", new_pan, pan);
        return 0;
    }

    pan = 0x0004; /* randomly chosen by fair dice roll ;-) */
    new_pan = cc2420_set_address(pan);

    if (new_pan != pan) {
        printf("new_pan [%d] != pan [%d] after set_address\n", new_pan, pan);
        return 0;
    }

    new_pan = cc2420_get_address();

    if (new_pan != pan) {
        printf("new_pan [%d] != pan [%d] after get_address\n", new_pan, pan);
        return 0;
    }

    return 1;
}

int main(void)
{
    transceiver_init(TRANSCEIVER_CC2420);

    if (!test_set_channel()) {
        printf("test_set_channel failed.\n");
        return 1;
    };
    if (!test_get_channel()) {
        printf("test_get_channel failed.\n");
        return 1;
    };
    if (!test_get_set_address()) {
        printf("test_get_set_address failed.\n");
        return 1;
    };
    if (!test_get_set_address_long()) {
        printf("test_get_set_address_long failed.\n");
        return 1;
    };
    if (!test_get_set_pan()) {
        printf("test_get_set_pan failed.\n");
        return 1;
    };

    printf("All tests successful.\n");
    return 0;
}

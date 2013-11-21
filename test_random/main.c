/*
 * Copyright (C) 2013 René Kijewski <rene.kijewski@fu-berlin.de>
 * Copyright (C) 2013 Christian Mehlis <christian.mehlis@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "random.h"

#define COUNT (10 * 1000)
#define BUCKETS (256)

int tops[BUCKETS] = {0}, bottoms[BUCKETS] = {0};

int main(void)
{
    uint32_t init[4] = { 0x123, 0x234, 0x345, 0x456 }, length = 4;
    genrand_init_by_array(init, length);
    printf("%d outputs of genrand_uint32()\n", COUNT);

    for (int i = 0; i < COUNT; i++) {
        uint32_t val = genrand_uint32();
        ++bottoms[val % BUCKETS];
        ++tops[val >> (32 - 8)];
    }

    puts("Tops:");

    for (int i = 0; i < BUCKETS; ++i) {
        printf("% 3d ", tops[i]);
    }

    puts("\nBottoms:");

    for (int i = 0; i < BUCKETS; ++i) {
        printf("% 3d ", bottoms[i]);
    }

    puts("");
    return 0;
}

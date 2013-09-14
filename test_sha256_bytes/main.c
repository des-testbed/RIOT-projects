#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "hwtimer.h"
#include "sha256.h"

unsigned char hash[SHA256_DIGEST_LENGTH];
#define myseed 0x83d385c0 /* random number */

#define BUF_SIZE 120 /* bytes */
uint8_t buf[BUF_SIZE];
#define COUNT (1 * 1000)

static void buf_fill(uint32_t *buf, int len)
{
    for (int k = 0; k < len; k++) {
        buf[k] = genrand_uint32();
    }
}

int main(void)
{
    hwtimer_init();
    genrand_init(myseed);

    unsigned long t1 = hwtimer_now();
    for (int i = 0; i < COUNT; i++) {
        buf_fill((uint32_t *) &buf, (BUF_SIZE / sizeof(uint32_t)));
        SHA256((uint32_t *) &buf, (BUF_SIZE / sizeof(uint32_t)), &hash);
#if 0
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            printf("%02x", hash[i]);
        }
        printf("\n");
#endif
    }
    unsigned long t2 = hwtimer_now();
    printf("hashing %d elements with %d bytes took %" PRIu32 "ms\n", COUNT,
            BUF_SIZE, (uint32_t) HWTIMER_TICKS_TO_US(t2-t1) / 1000);

    return 0;
}

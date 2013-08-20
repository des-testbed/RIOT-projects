#include <stdio.h>
#include <string.h>

#include "hashes.h"
#include "bloom.h"

#include "A.h"
#include "B.h"

int main(void)
{
    struct bloom_t *bloom =
        bloom_new(1 << 9, 6, fnv_hash, sax_hash, sdbm_hash, djb2_hash, kr_hash, dek_hash);

    printf("Testing Bloom filter.\n\n");
    printf("m: %zd\nk: %zd\n\n", bloom->m, bloom->k);

    for (int i = 0; i < lenB; i++) {
        bloom_add(bloom, B[i]);
        printf("Added \"%s\"\n", B[i]);
    }

    int in = 0;
    int not_in = 0;

    for (int i = 0; i < lenA; i++) {
        if (bloom_check(bloom, A[i])) {
            in++;
        }
        else {
            not_in++;
        }
    }

    printf("\n%d elements probably in the filter.\n", in);
    printf("\n%d elements not in the filter.\n", not_in);

    bloom_del(bloom);
    printf("\nAll done!\n");
    return 0;
}


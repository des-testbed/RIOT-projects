#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sha256.h"

unsigned char hash[SHA256_DIGEST_LENGTH];

void sha256(const char *str)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }

    printf("\n");
}

int main()
{
    sha256("1234567890_1");
    sha256("1234567890_2");
    sha256("1234567890_3");
    sha256("1234567890_4");
    return 0;
}

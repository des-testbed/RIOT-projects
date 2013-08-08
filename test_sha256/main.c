#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sha256.h"

unsigned char hash[SHA256_DIGEST_LENGTH];

void sha256(const char *str, const char *expected)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);

    printf("Input:      %s\n"
           "Expected:   %s\n"
           "Calculated: ", str, expected);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n\n");
}

int main()
{
    sha256("1234567890_1", "3eda9ffe5537a588f54d0b2a453e5fa932986d0bc0f9556924f5c2379b2c91b0");
    sha256("1234567890_2", "a144d0b4d285260ebbbab6840baceaa09eab3e157443c9458de764b7262c8ace");
    sha256("1234567890_3", "9f839169d293276d1b799707d2171ac1fd5b78d0f3bc7693dbed831524dd2d77");
    sha256("1234567890_4", "6c5fe2a8e3de58a5e5ac061031a8e802ae1fb9e7197862ec1aedf236f0e23475");
    sha256("0123456789abcde-0123456789abcde-0123456789abcde-0123456789abcde-",
           "945ab9d52b069923680c2c067fa6092cbbd9234cf7a38628f3033b2d54d3d3bf");
    return 0;
}

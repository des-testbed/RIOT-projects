/*
 * Copyright (C) 2013 Christian Mehlis <christian.mehlis@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

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

int main(void)
{
    sha256("1234567890_1",
           "3eda9ffe5537a588f54d0b2a453e5fa932986d0bc0f9556924f5c2379b2c91b0");
    sha256("1234567890_2",
           "a144d0b4d285260ebbbab6840baceaa09eab3e157443c9458de764b7262c8ace");
    sha256("1234567890_3",
           "9f839169d293276d1b799707d2171ac1fd5b78d0f3bc7693dbed831524dd2d77");
    sha256("1234567890_4",
           "6c5fe2a8e3de58a5e5ac061031a8e802ae1fb9e7197862ec1aedf236f0e23475");
    sha256("0123456789abcde-0123456789abcde-0123456789abcde-0123456789abcde-",
           "945ab9d52b069923680c2c067fa6092cbbd9234cf7a38628f3033b2d54d3d3bf");
    sha256("Franz jagt im komplett verwahrlosten Taxi quer durch Bayern",
           "d32b568cd1b96d459e7291ebf4b25d007f275c9f13149beeb782fac0716613f8");
    sha256("Frank jagt im komplett verwahrlosten Taxi quer durch Bayern",
           "78206a866dbb2bf017d8e34274aed01a8ce405b69d45db30bafa00f5eeed7d5e");
    sha256("",
           "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");

    return 0;
}

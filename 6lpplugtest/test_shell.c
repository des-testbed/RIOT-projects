#ifdef MODULE_SHELL
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "cpu-conf.h"
#include "board_uart0.h"
#include "posix_io.h"
#include "shell.h"
#include "net_if.h"

#include "test_shell.h"
#include "test_utils.h"
#include "test_format.h"
#include "test_hc.h"
#include "test_nd.h"
#include "test_nd_hc.h"

uint8_t hexchar_to_decdigit(char c) {
    if (c >= '0' && c <= '9') { 
        return (uint8_t)c - 48;
    }
    else if (c >= 'A' && c <= 'F') {
        return (uint8_t)c - 55;
    }
    else if (c >= 'a' && c <= 'f') {
        return (uint8_t)c - 87;
    } else {
        return 0xff;
    }
}

uint16_t hexstring_to_short(char *str) {
    uint16_t value = 0;
    uint8_t count = 0;

    while (*str && count < 4) {
        uint8_t tmp = hexchar_to_decdigit(*str);
        if (tmp != 0xff) {
            value <<= 4;
            value += (uint16_t)value;
        }
        str++;
        count++;
    } 
    return value;
}

void usage(void)
{
    puts("Usage: test {format|hc|nd|nd_hc} <test_number> <device> [<test parameters>]\n");
}

void usage_one_param(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s <destination address>\n",
           group, number, device);
}

void usage_one_param_router(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s <router prefix>\n",
           group, number, device);
}

void usage_opt_router(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s [router <router prefix>]\n",
           group, number, device);
}


void usage_param_router_list(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s <ping destination address> <ping data> <router prefix1> <router prefix2> ...\n",
           group, number, device);
}

void usage_two_param(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s <ping destination address> <ping data>\n",
           group, number, device);
}

void usage_two_param_opt_router(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s [router <router prefix>] <ping destination address> <ping data>\n",
           group, number, device);
}

void usage_two_param_router(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s <router prefix> <expected host address>\n",
           group, number, device);
}

void usage_three_param_router(char *group, int number, char *device)
{
    printf("Usage: test %s %d %s <ping destination address> <ping data> <router prefix>\n",
           group, number, device);
}

void sixlpplugtest_test(int argc, char **argv)
{
    char *group, *device, *tmp;
    int number, i;

    if (argc < 4) {
        usage();
        return;
    }

    group = argv[1];
    tmp = argv[2];
    device = argv[3];

    number = atoi(tmp);

    for (i = 0; group[i] != 0; i++) {
        group[i] = (char)tolower((int)group[i]);
    }

    for (i = 0; device[i] != 0; i++) {
        device[i] = (char)tolower((int)device[i]);
    }

    if (strcmp(group, "format") == 0) {
        switch (number) {
            case (1):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format01_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format01_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (2):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format02_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format02_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (3):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format03_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format03_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (4):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format04_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format04_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (5):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format05_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format05_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (6):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format06_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format06_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (7):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format07_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format07_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (8):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format08_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_format08_eut2(argv[4], argv[5]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            default:
                puts("<number> for group FORMAT must be between 1 and 8.\n");
                return;
        }
    }
    else if (strcmp(group, "hc") == 0) {
        switch (number) {
            case (1):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_hc01_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc01_eut2(argv[4]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (2):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_hc02_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc02_eut2(argv[4]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
            case (3):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_hc03_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc03_eut2(argv[4]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
 
            case (4):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_hc04_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc04_eut2(argv[4]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
 
            case (5):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 6) {
                        usage_two_param_router(group, number, device);
                    }
                    sixlowpan_hc05_6lr(argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc05_host(argv[4]);
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;
 
            case (6):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 6) {
                        usage_two_param_router(group, number, device);
                    }
                    sixlowpan_hc06_6lr(argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc06_host(argv[4]);
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (7):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 6) {
                        usage_two_param_router(group, number, device);
                    }
                    sixlowpan_hc07_6lr(argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc07_host(argv[4]);
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (8):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 6) {
                        usage_two_param_router(group, number, device);
                    }
                    sixlowpan_hc08_6lr(argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc08_host(argv[4]);
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (9):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_hc09_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc09_eut2(argv[4]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
 
            case (10):
                if (strcmp(device, "eut1") == 0) {
                    if (argc < 6) {
                        usage_two_param(group, number, device);
                    }
                    sixlowpan_hc10_eut1(argv[4], argv[5]);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_one_param(group, number, device);
                    }
                    sixlowpan_hc10_eut2(argv[4]);
                }
                else {
                    puts("<device> must be \"eut1\" or \"eut2\"\n");
                }
                break;
 
            default:
                puts("<number> for group HC must be between 1 and 10.\n");
                return;
        }
    }
    else if (strcmp(group, "nd") == 0) {
        switch (number) {
            case (1):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 7) {
                        usage_three_param_router(group, number, device);
                    }
                    sixlowpan_nd01_6lr(argv[6], argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd01_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (2):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 7) {
                        usage_three_param_router(group, number, device);
                    }
                    sixlowpan_nd02_6lr(argv[6], argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd02_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (3):
                if (strcmp(device, "6lr") == 0) {
                    sixlowpan_nd03_6lr();
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd03_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (4):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 7) {
                        usage_three_param_router(group, number, device);
                    }
                    sixlowpan_nd04_6lr(argv[6], argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd04_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (5):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 5) {
                        usage_one_param_router(group, number, device);
                    }
                    sixlowpan_nd05_6lr(argv[4]);
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd05_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (6):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 8) {
                        usage_param_router_list(group, number, device);
                    }
                    sixlowpan_nd06_6lr(argc - 6, &argv[6], argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd06_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            case (7):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 8) {
                        usage_param_router_list(group, number, device);
                    }
                    sixlowpan_nd07_6lr(argc - 6, &argv[6], argv[4], argv[5]);
                }
                else if (strcmp(device, "host") == 0) {
                    sixlowpan_nd07_host();
                }
                else {
                    puts("<device> must be \"6lr\" or \"host\"\n");
                }
                break;

            default:
                puts("<number> for group ND must be between 1 and 7.\n");
                return;
        } 
    }
    else if (strcmp(group, "nd_hc") == 0) {
        switch (number) {
            case (1):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 5) {
                        printf("Usage: test %s %d router <router prefix>\n",
                               group, number);
                    }
                    sixlowpan_nd_hc_6lr(argv[4],
                                        SLPT_6LR_FLAG_64BIT | 
                                            SLPT_6LR_FLAG_CONTEXT0 |
                                            SLPT_6LR_FLAG_STANDALONE);
                }
                else if (strcmp(device, "eut1") == 0) {
                    char *dest, *data;
                    if (argc < 6) {
                        usage_two_param_opt_router(group, number, device);
                    }
                    if (argc > 7) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        dest = argv[6];
                        data = argv[7];
                        sixlowpan_nd_hc_6lr(argv[5],
                                            SLPT_6LR_FLAG_64BIT | 
                                                SLPT_6LR_FLAG_CONTEXT0);
                    }
                    else {
                        dest = argv[4];
                        data = argv[5];
                    }
                    sixlowpan_nd_hc01_eut1(dest, data);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_opt_router(group, number, device);
                    }
                    if (argc > 6) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        sixlowpan_nd_hc_6lr(argv[5],
                                            SLPT_6LR_FLAG_64BIT | 
                                                SLPT_6LR_FLAG_CONTEXT0);
                    }
                    sixlowpan_nd_hc01_eut2();
                }
                else {
                    puts("<device> must be \"6lr\", \"eut1\" or \"eut2\"\n");
                }
                break;

            case (2):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 5) {
                        printf("Usage: test %s %d router <router prefix>\n",
                               group, number);
                    }
                    sixlowpan_nd_hc_6lr(argv[4],
                                        SLPT_6LR_FLAG_CONTEXT0 |
                                            SLPT_6LR_FLAG_STANDALONE);
                }
                else if (strcmp(device, "eut1") == 0) {
                    char *dest, *data;
                    if (argc < 6) {
                        usage_two_param_opt_router(group, number, device);
                    }
                    if (argc > 7) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        dest = argv[6];
                        data = argv[7];
                        sixlowpan_nd_hc_6lr(argv[5], SLPT_6LR_FLAG_CONTEXT0);
                    }
                    else {
                        dest = argv[4];
                        data = argv[5];
                    }
                    sixlowpan_nd_hc02_eut1(dest, data);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_opt_router(group, number, device);
                    }
                    if (argc > 6) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        sixlowpan_nd_hc_6lr(argv[5], SLPT_6LR_FLAG_CONTEXT0);
                    }
                    sixlowpan_nd_hc02_eut2();
                }
                else {
                    puts("<device> must be \"6lr\", \"eut1\" or \"eut2\"\n");
                }
                break;

            case (3):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 5) {
                        printf("Usage: test %s %d router <router prefix>\n",
                               group, number);
                    }
                    sixlowpan_nd_hc_6lr(argv[4], SLPT_6LR_FLAG_64BIT | 
                                        SLPT_6LR_FLAG_STANDALONE);
                }
                else if (strcmp(device, "eut1") == 0) {
                    char *dest, *data;
                    if (argc < 6) {
                        usage_two_param_opt_router(group, number, device);
                    }
                    if (argc > 7) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        dest = argv[6];
                        data = argv[7];
                        sixlowpan_nd_hc_6lr(argv[5], SLPT_6LR_FLAG_64BIT);
                    }
                    else {
                        dest = argv[4];
                        data = argv[5];
                    }
                    sixlowpan_nd_hc03_eut1(dest, data);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_opt_router(group, number, device);
                    }
                    if (argc > 6) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        sixlowpan_nd_hc_6lr(argv[5], SLPT_6LR_FLAG_64BIT);
                    }
                    sixlowpan_nd_hc03_eut2();
                }
                else {
                    puts("<device> must be \"6lr\", \"eut1\" or \"eut2\"\n");
                }
                break;

            case (4):
                if (strcmp(device, "6lr") == 0) {
                    if (argc < 5) {
                        printf("Usage: test %s %d router <router prefix>\n",
                               group, number);
                    }
                    sixlowpan_nd_hc_6lr(argv[4], SLPT_6LR_FLAG_STANDALONE);
                }
                else if (strcmp(device, "eut1") == 0) {
                    char *dest, *data;
                    if (argc < 7) {
                        usage_two_param_opt_router(group, number, device);
                    }
                    if (argc > 6) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        dest = argv[6];
                        data = argv[7];
                        sixlowpan_nd_hc_6lr(argv[5], 0);
                    }
                    else {
                        dest = argv[4];
                        data = argv[5];
                    }
                    sixlowpan_nd_hc04_eut1(dest, data);
                }
                else if (strcmp(device, "eut2") == 0) {
                    if (argc < 5) {
                        usage_opt_router(group, number, device);
                    }
                    if (argc > 6) {
                        if (strcmp(argv[4], "router") != 0) {
                            usage_two_param_opt_router(group, number, device);
                        }
                        sixlowpan_nd_hc_6lr(argv[5], 0);
                    }
                    sixlowpan_nd_hc04_eut2();
                }
                else {
                    puts("<device> must be \"6lr\", \"eut1\" or \"eut2\"\n");
                }
                break;

            default:
                puts("<number> for group ND_HC must be between 1 and 4.\n");
                return;
        }
    }
    else {
        usage();
    }
}

const shell_command_t shell_commands[] = {
    {"test", "Runs a 6LoWPAN plugtest.\n", 
        sixlpplugtest_test},
    {NULL, NULL, NULL}
};

void sixlpplugtest_shell_init(void) {
    posix_open(uart0_handler_pid, 0);

    shell_t shell;
    shell_init(&shell, shell_commands, UART0_BUFSIZE, uart0_readc, uart0_putc);

    shell_run(&shell);
}
#else
void sixlpplugtest_empty(void) {
    return;
}
#endif

#include "ipv6.h"
#include "msg.h"
#include "net_if.h"
#include "vtimer.h"
#include "sixlowpan.h"

#include "test_format.h"
#include "test_utils.h"

#if defined(MODULE_SHELL) || defined(ND)
int sixlowpan_nd_init(ipv6_addr_t *prefix)
{
    sixlowpan_lowpan_set_iphc_status(LOWPAN_IPHC_ENABLE);
    ipv6_set_default_hop_limit(64);

    if (net_if_set_channel(IF_ID, CHANNEL) < 0) {
        printf("Can not set channel.\n");
        return 0;
    }

    if (net_if_set_pan_id(IF_ID, PAN_ID) < 0) {
        printf("Can not set PAN ID %d.\n", PAN_ID);
        return 0;
    }

    if (prefix) {
        return sixlowpan_lowpan_init_adhoc_interface(IF_ID, prefix);
    }
    else {
        return sixlowpan_lowpan_init_interface(IF_ID);
    }       
}

int sixlowpan_nd_init_long(ipv6_addr_t *prefix) {
    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_LONG);
    return sixlowpan_nd_init(prefix); 
}

int sixlowpan_nd_init_short(ipv6_addr_t *prefix) {
    net_if_set_src_address_mode(IF_ID, NET_IF_TRANS_ADDR_M_SHORT);
    return sixlowpan_nd_init(prefix); 
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST1) && defined(EUT1))
int sixlowpan_nd01_host(void)
{
    if (!sixlowpan_nd_init_long(NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    SUCCESS("TD_6LoWPAN_ND_01 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST1) && defined(EUT2))
int sixlowpan_nd01_6lr(char *prefix_str, char *host_str, char *data)
{
    ipv6_addr_t prefix, host;
    int prefix_len;

    if (!slplugtest_utils_init_ll_eut_addr(&host, host_str)) {
        SILENT_ERROR();
    }

    if (!slplugtest_utils_init_prefix(&prefix, &prefix_len, prefix_str)) {
        ERROR("Error parsing prefix string\n");
    }

    if (!sixlowpan_nd_init_long(&prefix)) {
        ERROR("Interface initialization failed.\n");
    }

    vtimer_usleep(1000);

    icmpv6_send_echo_request(&host, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_ND_01 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST2) && defined(EUT1))
int sixlowpan_nd02_host(void)
{
    if (!sixlowpan_nd_init_short(NULL)) {
        ERROR("Interface initialization failed.\n");
    }

    SUCCESS("TD_6LoWPAN_ND_02 [EUT1]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST2) && defined(EUT2))
int sixlowpan_nd02_6lr(char *prefix_str, char *host_str, char *data)
{
    ipv6_addr_t prefix, host;
    int prefix_len;

    if (!slplugtest_utils_init_ll_eut_addr(&host, host_str)) {
        SILENT_ERROR();
    }

    if (!slplugtest_utils_init_prefix(&prefix, &prefix_len, prefix_str)) {
        ERROR("Error parsing prefix string\n");
    }

    if (!sixlowpan_nd_init_short(&prefix)) {
        ERROR("Interface initialization failed.\n");
    }

    vtimer_usleep(1000);

    icmpv6_send_echo_request(&host, 1, 1, (uint8_t *) data, 4);

    SUCCESS("TD_6LoWPAN_ND_02 [EUT2]\n");
    return 1;
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST3) && defined(EUT1))
int sixlowpan_nd03_host(void)
{
    ERROR("NUD not implemented in RIOT yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST3) && defined(EUT2))
int sixlowpan_nd03_6lr(void)
{
    ERROR("NUD not implemented in RIOT yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST4) && defined(EUT1))
int sixlowpan_nd04_6lr(char *prefix, char *host_str, char *data)
{
    (void)prefix;
    (void)host_str;
    (void)data;
    ERROR("NUD not implemented in RIOT yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST4) && defined(EUT2))
int sixlowpan_nd04_host(void)
{
    ERROR("NUD not implemented in RIOT yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST5) && defined(EUT1))
int sixlowpan_nd05_6lr(char *prefix)
{
    (void)prefix;
    ERROR("NUD not implemented in RIOT yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST5) && defined(EUT2))
int sixlowpan_nd05_host(void)
{
    ERROR("NUD not implemented in RIOT yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST6) && defined(EUT1))
int sixlowpan_nd06_host(void)
{
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST6) && defined(EUT2))
int sixlowpan_nd06_6lr(char *prefix_list, char *host_str, char *data)
{
    (void)prefix_list;
    (void)host_str;
    (void)data;
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST7) && defined(EUT1))
int sixlowpan_nd07_host(void)
{
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND) && defined(TEST7) && defined(EUT2))
int sixlowpan_nd07_6lr(char *prefix_list, char *host_str, char *data)
{
    (void)prefix_list;
    (void)host_str;
    (void)data;
    ERROR("Test not implemented yet.\n");
}
#endif

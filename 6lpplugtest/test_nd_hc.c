/*
 * Copyright (C) 2013-14 Martin Lenders.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */
#include "test_nd_hc.h"
#include "test_utils.h"

#if defined(MODULE_SHELL) || defined(ND_HC)
void sixlowpan_nd_hc_6lr(char *prefix, uint8_t flags)
{
    (void)prefix;
    (void)flags;
    printf("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST1) && defined(EUT1))
int sixlowpan_nd_hc01_eut1(char *eut2_addr, char *data)
{
    (void)eut2_addr;
    (void)data;
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST1) && defined(EUT2))
int sixlowpan_nd_hc01_eut2(void)
{
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST2) && defined(EUT1))
int sixlowpan_nd_hc02_eut1(char *eut2_addr, char *data)
{
    (void)eut2_addr;
    (void)data;
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST2) && defined(EUT2))
int sixlowpan_nd_hc02_eut2(void)
{
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST3) && defined(EUT1))
int sixlowpan_nd_hc03_eut1(char *eut2_addr, char *data)
{
    (void)eut2_addr;
    (void)data;
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST3) && defined(EUT2))
int sixlowpan_nd_hc03_eut2(void)
{
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST4) && defined(EUT1))
int sixlowpan_nd_hc04_eut1(char *eut2_addr, char *data)
{
    (void)eut2_addr;
    (void)data;
    ERROR("Test not implemented yet.\n");
}
#endif

#if defined(MODULE_SHELL) || (defined(ND_HC) && defined(TEST4) && defined(EUT2))
int sixlowpan_nd_hc04_eut2(void)
{
    ERROR("Test not implemented yet.\n");
}
#endif

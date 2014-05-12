/*
 * main.c - Test application for OpenWSN on RIOT
 * Copyright (C) 2014 Thomas Eichinger
 *
 * Author : Thomas Eichinger <thomas.eichinger@fu-berlin.de>
 *
 * This file subject to the terms and conditions of the LGPLv2. See the file
 * LICENSE in the  top level directory for more details.
 */

#include "openwsn.h"

void main(void)
{
    openwsn_start_thread();
}

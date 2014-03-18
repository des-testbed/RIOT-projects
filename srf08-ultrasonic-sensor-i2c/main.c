/*
 * main.c - Main function of the SRF08 ultrasonic sensor project.
 *
 * Copyright (C) 2013 Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 *
 * The source code is licensed under the LGPLv2 license,
 * See the file LICENSE for more details.
 */

/**
 * @file
 * @internal
 * @brief               Initialize the SRF08 ultrasonic sensor and start a
 *                      continuous sampling of the distance measures.
 *                      Up to 17 distances indicating echo's from distant
 *                      objects can be measured. The SRF08 ultrasonic sensor
 *                      has a range of 3 cm to 6 m.
 *
 * @author              Freie Universität Berlin, Computer Systems & Telematics
 * @author              Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version             $Revision: 3855 $
 *
 * @note                $Id: main.c 3855 2013-09-04 15:39:11 kasmi $
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "i2c.h"
#include "gpioint.h"
#include "hwtimer.h"
#include "board.h"
#include "srf08-ultrasonic-sensor.h"


int main(void)
{
    // init ktimer
    hwtimer_init();
    printf("# %-70s%10s\n", "hwtimer", "...[OK]");

    // init the SRF08 ultrasonic sensor
    if (srf08_init(SRF08_I2C_INTERFACE, 400000)) {
        printf("# %-70s%10s\n", "SRF08 ultrasonic sensor initialization",
               "...[OK]");
    }
    else {
        printf("# %-70s%10s\n", "SRF08 initialization", "...[FAILED]");
        return EXIT_FAILURE;
    }

    // switch on the green LED
    LED_GREEN_ON;
    puts("MCU is ready\n");
    srf08_start_ranging(SRF08_REAL_RANGING_MODE_CM);
    return EXIT_SUCCESS;
}

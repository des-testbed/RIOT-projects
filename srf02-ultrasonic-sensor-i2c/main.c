/*
 * main.c - Main function of the SRF02 ultrasonic sensor project.
 * Copyright (C) 2013 Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 *
 * The source code is licensed under the LGPLv2 license,
 * See the file LICENSE for more details.
 */

/**
 * @file
 * @internal
 * @brief       Initialize the SRF02 ultrasonic sensor and start a continuous
 *              sampling of the distance measures. The SRF02 ultrasonic sensor
 *              has a range of 16 cm to 6 m.
 *
 * @author      Freie Universität Berlin, Computer Systems & Telematics
 * @author      Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version     $Revision: 3855 $
 *
 * @note        $Id: main.c 3855 2013-09-04 15:25:19 kasmi $
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lpc23xx.h"    /* LPC23xx definitions */
#include "i2c.h"
#include "gpioint.h"
#include "hwtimer.h"
#include "board.h"
#include "srf02-ultrasonic-sensor.h"



int main(void)
{

    // init ktimer
    hwtimer_init();
    printf("# %-70s%10s\n", "hwtimer", "...[OK]");

    // init the srf02 sensor
    if (srf02_init(SRF02_I2C_INTERFACE, 400000)) {
        printf("# %-70s%10s\n", "SRF02 ultrasonic sensor initialization",
               "...[OK]");
    }
    else {
        printf("# %-70s%10s\n", "SRF02 initialization", "...[FAILED]");
        return EXIT_FAILURE;
    }

    puts("MCU is ready\n");
    // switch on the green LED
    LED_GREEN_ON;
    srf02_start_ranging(SRF02_REAL_RANGING_MODE_CM);
    return EXIT_SUCCESS;
}


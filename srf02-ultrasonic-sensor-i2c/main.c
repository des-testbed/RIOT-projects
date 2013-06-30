/*
 * main.c - Main function of the SRF02 ultrasonic sensor project.
 * Copyright (C) 2013 Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 *
 * The source code is licensed under the LGPLv2 license, See the file LICENSE for more details.
 */

/**
 * @file
 * @internal
 * @brief	Initialize the SRF02 ultrasonic sensor and start a continuous sampling of the distance 
 *		measures. The SRF02 ultrasonic sensor has a range of 16 cm to 6 m.
 *
 * @author 	Freie Universität Berlin, Computer Systems & Telematics
 * @author	Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version	$Revision: 3854 $
 *
 * @note	$Id: main.c 3854 2013-06-24 15:40:01 zkasmi $
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lpc23xx.h" 	/* LPC23xx/24xx definitions */
#include "i2c.h"
#include "gpioint.h"
#include "hwtimer.h"
#include "board.h"
#include "srf02-ultrasonic-sensor.h"



/*******************************************************************************
 **   Main Function  main()
 *******************************************************************************/

int main(void) {

	// init ktimer
	hwtimer_init();
	printf("# %-70s%10s\n", "hwtimer", "...[OK]");

	// init the srf02 sensor
	if (srf02_init(SRF02_I2C_INTERFACE, 400000)) {
			printf("# %-70s%10s\n", "SRF02 ultrasonic sensor initialization", "...[OK]");
		}
	puts("LPC2387 is ready\n");
	// switch on the green LED
	LED_GREEN_ON;
	printf("PI=%f\n", 3.134343);
	srf02_start_ranging();

	return EXIT_SUCCESS;
}


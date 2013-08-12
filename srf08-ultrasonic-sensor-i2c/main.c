/*
 * main.c - Main function of the SRF08 ultrasonic sensor project.
 * Copyright (C) 2013 Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 *
 * The source code is licensed under the LGPLv2 license, 
 * See the file LICENSE for more details.
 */

/**
 * @file
 * @internal
 * @brief		Initialize the SRF08 ultrasonic sensor and start a continuous 
 *			sampling of the distance measures.
 * 		  	Up to 17 distances indicating echo's from distant objects can be 
 *			measured. The SRF08 
 *			ultrasonic sensor has a range of 3 cm to 6 m.
 *
 * @author		Freie Universität Berlin, Computer Systems & Telematics
 * @author		Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version		$Revision: 3854 $
 *
 * @note		$Id: main.c 3854 2013-06-24 19:40:01 zkasmi $
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lpc23xx.h"	/* LPC23xx definitions */
#include "i2c.h"
#include "gpioint.h"
#include "hwtimer.h"
#include "board.h"
#include "srf08-ultrasonic-sensor.h"

#define SRF02_DEFAULT_ADDR 		112
#define SRF02_COMMAND_REG		0x0
#define SRF02_RANGE_HIGH_BYTE		0x2
#define SRF02_RANGE_LOW_BYTE		0x3
#define SRF02_REAL_RANGING_MODE_CM	0x51

/*******************************************************************************
 *
 * Main Function  main()
 *
 *******************************************************************************/

int main(void) {

	// init ktimer
	hwtimer_init();
	printf("# %-70s%10s\n", "hwtimer", "...[OK]");

	// init the SRF08 ultrasonic sensor
	if (srf08_init(SRF08_I2C_INTERFACE, 400000)) {
		printf("# %-70s%10s\n", "SRF08 ultrasonic sensor initialization", "...[OK]");
	}

	// switch on the green LED
	LED_GREEN_ON;
	puts("LPC2387 is ready\n");
	srf08_start_ranging();

	return EXIT_SUCCESS;
}


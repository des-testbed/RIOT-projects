/*
 * main.c - Main function of the LM75 temperature sensor project.
 * Copyright (C) 2013 Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 *
 * The source code is licensed under the LGPLv2 license, See the file LICENSE for more details.
 */

/**
 * @file
 * @internal
 * @brief		initializes the i2c interface and starts the LM75A temperature sampling function
 *
 * @author      Freie Universität Berlin, Computer Systems & Telematics
 * @author		Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version     $Revision: 3854 $
 *
 * @note		$Id: main.c 3854 2013-05-27 15:40:01 zkasmi $
 */

#include <stdio.h>
#include <stdlib.h>
#include "lpc23xx.h"	/* LPC23xx/24xx definitions */
#include "i2c.h"
#include "gpioint.h"
#include "hwtimer.h"
#include "board.h"
#include "lm75a-temp-sensor.h"

static void temperature_ext_interr_handler(void) {
	puts("The external interrupt handler entered....\n");
	lm75A_set_in_alarm(true);
	LED_GREEN_OFF;
	puts("....The external interrupt handler ended\n");
}

static void temperature_ext_interrupt_task(void) {
	int i;

	for (i = 0; i < 30; i++) {
		puts(
				"ALARMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM !!\n");

	}
	LED_GREEN_OFF;
}

/*******************************************************************************
 **   Main Function  main()
 *******************************************************************************/
int main(void) {

	// init ktimer
	hwtimer_init();
	printf("# %-70s%10s\n", "hwtimer", "...[OK]");

	// enable interrupt handling on IO pin
	gpioint_init();

	//switch on the green LED
	LED_GREEN_ON;

	//init the I2C
	if (lm75A_init(LM75A_I2C_INTERFACE, 100000, temperature_ext_interr_handler)) {
		printf("# %-70s%10s\n", "lm75a initialization", "...[OK]");
	} else {
		printf("# %-70s%10s\n", "lm75a initialization", "...[FAILED]");
	}
	puts("LPC2387 is ready\n");
	printf("PI=%f\n", 3.134343);
	lm75A_start_sensor_sampling(temperature_ext_interrupt_task);

	return EXIT_SUCCESS;
}


/*
 * main.c - Main function of the lpc2387 external interrupts project.
 * Copyright (C) 2013 Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 *
 * This source code is licensed under the GNU General Public License,
 * Version 3. See the file LICENSE for more details.
 */

/**
 * @file
 * @internal
 * @brief	shows how to set up the external interrupts for the LPC2387
 *
 * @author      Freie Universität Berlin, Computer Systems & Telematics
 * @author	Zakaria Kasmi <zkasmi@inf.fu-berlin.de>
 * @version     $Revision: 3854 $
 *
 * @note	$Id: main.c 3854 2013-05-27 15:40:01 zkasmi $
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "gpioint.h"
#include "lpc2387.h"
#include "hwtimer.h"

#define PORT_NUM	2
#define PIN_NUM		BIT3

volatile bool flag; //volatile otherwise is the variable from the compiler optimized and no interrupt is triggered ??

bool ext_irq_handler_register(int32_t port_num, uint32_t pin_bit_mask,
		int32_t flags, void* handler) {
	return gpioint_set(port_num, pin_bit_mask, flags, handler);
}

static void my_handler(void) {
	puts("handler entered");
	flag = true;

}

int main(void) {
	flag = false;
	uint32_t counter = 0;

	// init ktimer
	hwtimer_init();
	printf("# %-70s%10s\n", "ktimer", "...[OK]");

	// enable interrupt handling on IO pin
	gpioint_init();

	// register the handler for the external interrupt
	if (ext_irq_handler_register(PORT_NUM, PIN_NUM, GPIOINT_FALLING_EDGE,
			&my_handler)) {
		printf("# %-70s%10s\n", "External interrupt handler registration", "...[OK]");
	} else {
		printf("# %-70s%10s\n","External interrupt handler registration", "...[failed]");
	}

	puts("LPC2387 is ready");
	while (1) {
		if (flag) {
			flag = false;
			counter++;
			printf("The interrupt number %lu is triggered\n", counter);
		}
		//hwtimer_wait(HWTIMER_TICKS(100000));
	}
	return EXIT_SUCCESS;
}

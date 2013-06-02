#include <stdio.h>
#include "vtimer.h"
#include "board.h"

#define MSEC (1000)
#define SEC (1000 * MSEC)

int main(void) {
	LED_RED_ON();
	printf("Hello World!\n");

	vtimer_usleep(5 * SEC);

	LED_RED_OFF();
	LED_GREEN_ON();
	printf("done!\n");

	return 0;
}

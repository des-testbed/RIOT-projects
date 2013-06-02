#include <stdio.h>
#include <hwtimer.h>

int main(void) {
	LED_RED_ON();
	printf("Hello World!\n");
	hwtimer_spin(5 * 1000 * 1000);
	LED_RED_OFF();
	LED_GREEN_ON();
	printf("done!\n");
	return 0;
}

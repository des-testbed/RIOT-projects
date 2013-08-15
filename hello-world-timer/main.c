#include "vtimer.h"
#include "thread.h"
#include "timex.h"
#include "board.h"

#define MSEC (1000)
#define SEC (1000 * MSEC)

vtimer_t t1;
timex_t t_time;
int timer_over_pid;
char timer_over_buf[KERNEL_CONF_STACKSIZE_MAIN];

void blinker(void) {
	while(1) {
		LED_RED_TOGGLE;
		vtimer_usleep(SEC);
	}
}

int main(void) {
	
	LED_RED_ON;
#ifdef LED_GREEN_OFF
    LED_GREEN_OFF;
#endif

	timer_over_pid = thread_create(timer_over_buf,
	                               KERNEL_CONF_STACKSIZE_MAIN,
	                               PRIORITY_MAIN-1,
	                               CREATE_WOUT_YIELD | CREATE_STACKTEST,
	                               blinker,
	                               "blinker");

	while(1) {
#ifdef LED_GREEN_TOGGLE
	  LED_GREEN_TOGGLE;
#endif
	  vtimer_usleep(SEC);
	}

	return 0;
}

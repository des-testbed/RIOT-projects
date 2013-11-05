#include <stdio.h>

#include "vtimer.h"
#include "thread.h"
#include "msg.h"

char timer_stack[KERNEL_CONF_STACKSIZE_DEFAULT];

struct timer_msg {
	vtimer_t timer;
	timex_t interval;
	char* msg;
};

struct timer_msg msg_a = { .timer = {0}, .interval = { .seconds = 2, .microseconds = 0}, .msg = "Hello World" };
struct timer_msg msg_b = { .timer = {0}, .interval = { .seconds = 5, .microseconds = 0}, .msg = "This is a Test" };

void timer_thread(void) {
	printf("This is thread %d\n", thread_getpid());

	/* we need a queue if the second message arrives while the first is still processed */
	/* without a queue, the message would get lost */
	/* because of the way this timer works, there can be max 1 queued message */
	msg_t msgq[1];
	msg_init_queue(msgq, sizeof msgq);

	while (1) {
		msg_t m;
		msg_receive(&m);
		struct timer_msg* tmsg = (struct timer_msg*) m.content.ptr;
		printf("every %u.%us: %s\n", tmsg->interval.seconds, tmsg->interval.microseconds, tmsg->msg);
		if (vtimer_set_msg(&tmsg->timer, tmsg->interval, thread_getpid(), tmsg) != 0)
			puts("something went wrong");
	}
}

int main(void) {
	msg_t m;
	int pid = thread_create(timer_stack, sizeof timer_stack, PRIORITY_MAIN-1, CREATE_STACKTEST, timer_thread, "timer");

	puts("sending 1st msg");
	m.content.ptr = (char*) &msg_a;
	msg_send(&m, pid, false);

	puts("sending 2nd msg");
	m.content.ptr = (char*) &msg_b;
	msg_send(&m, pid, false);
}

#include <stdio.h>
#include "thread.h"
#include "msg.h"

char stack[KERNEL_CONF_STACKSIZE_MAIN];
void second_thread(void) {
	msg_t m;
	while(1) {
		msg_receive(&m);
		printf("2nd: got msg from %i\n", m.sender_pid);
		m.content.value++;
		msg_send(&m, m.sender_pid, true);
	}
}

int main(void) {
	msg_t m;
	int pid = thread_create(stack,
	                        KERNEL_CONF_STACKSIZE_MAIN,
	                        PRIORITY_MAIN-1,
	                        CREATE_WOUT_YIELD | CREATE_STACKTEST,
	                        second_thread,
	                        "pong");
	m.content.value = 1;
	while(1) {
		msg_send(&m, pid, true);
		msg_receive(&m);
		printf("Got msg with content %i\n", (int) m.content.value);
	}
}

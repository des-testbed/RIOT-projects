#include <stdio.h>
#include <thread.h>
#include <flags.h>
#include <kernel.h>

void second_thread(void) {
    printf("second_thread starting.\n");
    
    puts("2nd: running...");
}

char second_thread_stack[KERNEL_CONF_STACKSIZE_DEFAULT + KERNEL_CONF_STACKSIZE_PRINTF];

int main(void)
{
    (void) thread_create(second_thread_stack, sizeof(second_thread_stack), PRIORITY_MAIN-1, CREATE_WOUT_YIELD | CREATE_STACKTEST, second_thread, "nr2");
    puts("Main thread exiting...");
}

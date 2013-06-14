#define ENABLE_DEBUG 1

#include "vtimer.h"
#include "thread.h"
#include "timex.h"
#include "shell.h"
#include "board.h"
#include "posix_io.h"
#include "board_uart0.h"
#include "transceiver.h"

#define MSEC (1000)
#define SEC (1000 * MSEC)

timex_t start, end;
shell_t shell;

void print_teststart(char* str) {
  printf("[TEST_START]\n");
  vtimer_now(&start);
  timex_print(start);
}

void print_testend(char* str) {
  printf("[TEST_END]\n");
  vtimer_now(&end);
  timex_print(end);
  timex_t diff = timex_sub(end, start);
  timex_print(diff);
}

int shell_readc() {
  char c = 0;
  posix_read(uart0_handler_pid, &c, 1);
  return c;
}

void shell_putchar(int c) {
  putchar(c);
}

const shell_command_t shell_commands[] = {
  {"start_test", "", print_teststart},
  {"end_test", "", print_testend},
  {NULL, NULL, NULL}
};

int main(void) {

  transceiver_init(TRANSCEIVER_CC1100);



  vtimer_usleep(SEC);

  posix_open(uart0_handler_pid, 0);

  shell_init(&shell, shell_commands, uart0_readc, uart0_putc);
  shell_run(&shell);

  return 0;
}

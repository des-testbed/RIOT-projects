This project shows how to use own or the system shell commands. In order to use the system shell commands:
1. Additionally to the module: shell, shell_commands, uart0 and posix, the module for the corresponding system command is to include, e.g. module ps 
for the ps command (cf. the Makefile in the project root directory). 
2. the shell must be initialized as follows:
	shell_t sys_shell;
	shell_init(&sys_shell, NULL, shell_readc, shell_putchar);
	shell_run(&sys_shell);

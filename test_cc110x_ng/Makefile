export PROJECT = test_cc110x_ng
include ../Makefile.applications_common

export BOARD_WHITELIST = msba2

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

USEMODULE += config
USEMODULE += posix
USEMODULE += uart0
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += vtimer
USEMODULE += cc110x_ng
USEMODULE += auto_init

include $(RIOTBASE)/Makefile.include

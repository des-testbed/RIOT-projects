valgrind: CFLAGS += -g
valgrind: CFLAGS += -DHAVE_VALGRIND_VALGRIND_H

# name of your project
export PROJECT = debug_transceiver

# for easy switching of boards
ifeq (,$(BOARD))
export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT

ifeq (,$(findstring native,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else
ifneq (,$(findstring native,$(BOARD)))
USEMODULE += nativenet
endif

## Modules to include. 

USEMODULE += auto_init
USEMODULE += hwtimer
USEMODULE += transceiver
USEMODULE += posix
USEMODULE += uart0
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include
valgrind: all

endif

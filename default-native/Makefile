valgrind: CFLAGS += -g
valgrind: CFLAGS += -DHAVE_VALGRIND_VALGRIND_H

# name of your project
export PROJECT = default-native
#
# for easy switching of boards
export BOARD = native

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../RIOT
export RIOTBOARD =$(CURDIR)/../../boards

ifeq (,$(findstring native,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else

## Modules to include. 

USEMODULE += auto_init
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += posix
USEMODULE += vtimer
USEMODULE += rtc
USEMODULE += ltc4150
USEMODULE += config

# work in progress
USEMODULE += nativenet
USEMODULE += transceiver
USEMODULE += uart0

# not yet working:
#
#USEMODULE += sht11
#USEMODULE += fat

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include
valgrind: all
endif

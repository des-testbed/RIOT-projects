valgrind: CFLAGS += -g
valgrind: CFLAGS += -DHAVE_VALGRIND_VALGRIND_H

# name of your project
export PROJECT = default-native
#
# for easy switching of boards
export BOARD = native

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../RIOT

ifeq (,$(findstring native,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else

## Modules to include. 

# use auto_init with care, some modules still need to be initialized
# and most get confused if initialized twice
USEMODULE += auto_init

USEMODULE += config
USEMODULE += hwtimer
USEMODULE += ltc4150 # depends on hwtimer
USEMODULE += nativenet
USEMODULE += posix
USEMODULE += ps
USEMODULE += rtc
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += transceiver
USEMODULE += uart0
USEMODULE += vtimer

# as of yet unsupported modules:
#USEMODULE += fat
#USEMODULE += sht11

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include
valgrind: all
endif

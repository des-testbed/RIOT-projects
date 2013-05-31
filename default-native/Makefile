debug: CFLAGS += -g
debug: CFLAGS += -DENABLE_DEBUG

# name of your project
export PROJECT = default-native
#
# for easy switching of boards
export BOARD = native

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTBOARD =$(CURDIR)/../../boards

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
USEMODULE += cc110x_ng
USEMODULE += transceiver
USEMODULE += uart0

# not yet working:
#
#USEMODULE += sht11
#USEMODULE += fat

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/drivers/cc110x_ng/include/

include $(RIOTBASE)/Makefile.include

debug: all

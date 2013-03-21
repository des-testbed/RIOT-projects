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

# not yet working:
#
#USEMODULE += cc110x_ng
#USEMODULE += sht11
#USEMODULE += fat
#USEMODULE += uart0

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include

debug: all

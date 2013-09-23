####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../RIOT
#### ../../boards   for board definitions (if you have one or more)
####

# name of your project
export PROJECT =tlayer

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
export BOARD = msba2
endif

ifneq (,$(findstring msb-430,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTCPU =$(CURDIR)/../../RIOT/cpu
export RIOTBOARD =$(CURDIR)/../../boards

## Modules to include. 

USEMODULE += auto_init
USEMODULE += vtimer
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += config
ifeq ($(BOARD),native)
	USEMODULE += nativenet
else ifeq($(BOARD),msba2)
USEMODULE += cc110x_ng
endif
USEMODULE += transceiver
USEMODULE += net_help
USEMODULE += sixlowpan
USEMODULE += destiny
USEMODULE += uart0
USEMODULE += posix
USEMODULE += ltc4150

export INCLUDES += -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include -I$(RIOTBASE)/sys/net/destiny/include -I$(RIOTBASE)/sys/net/destiny -I$(RIOTBASE)/sys/net/sixlowpan/include -I$(RIOTBASE)/sys/net/net_help

include $(RIOTBASE)/Makefile.include
endif

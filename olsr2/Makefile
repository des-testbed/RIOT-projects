####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT =olsr_node

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../RIOT

USEPKG += oonf_api

export CFLAGS = -DRIOT -DENABLE_NAME -ggdb

## Modules to include. 

USEMODULE += auto_init
USEMODULE += rtc
USEMODULE += uart0
USEMODULE += posix
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += random
USEMODULE += config
USEMODULE += olsr2
ifeq ($(BOARD),native)
	USEMODULE += nativenet
	export CFLAGS += -DBOARD_NATIVE -DINIT_ON_START
endif
ifeq ($(BOARD),msba2)
	USEMODULE += gpioint
	USEMODULE += cc110x_ng
	export CFLAGS += -DBOARD_MSBA2 -DINIT_ON_START -DENABLE_LEDS
endif

export INCLUDES += -I$(RIOTBASE)/sys/net/include -I$(RIOTBASE)/sys/posix/include

include $(RIOTBASE)/Makefile.include

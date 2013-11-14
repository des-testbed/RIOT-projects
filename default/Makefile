####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../RIOT
#### ../../boards   for board definitions (if you have one or more)
####

# name of your project
export PROJECT = default

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT

# uncomment this to enable scheduler statistics for ps
#CFLAGS += -DSCHEDSTATISTICS

USEMODULE += posix
USEMODULE += uart0
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += vtimer
USEMODULE += auto_init
ifneq (,$(findstring msb-430,$(BOARD)))
	USEMODULE += sht11
endif
ifneq (,$(findstring wsn430-v1_3b,$(BOARD)))
	USEMODULE += cc110x_ng
endif
ifneq (,$(findstring wsn430-v1_4,$(BOARD)))
	USEMODULE += cc2420
endif
ifneq (,$(findstring msb-430h,$(BOARD)))
	USEMODULE += cc110x_ng
endif
ifneq (,$(findstring msba2,$(BOARD)))
	USEMODULE += sht11
	USEMODULE += ltc4150
	USEMODULE += rtc
	USEMODULE += mci
	USEMODULE += cc110x_ng
	USEMODULE += config
endif
ifneq (,$(findstring native,$(BOARD)))
	USEMODULE += ltc4150
	USEMODULE += rtc
	USEMODULE += nativenet
	USEMODULE += transceiver
	USEMODULE += config
endif

export INCLUDES = -I${RIOTBASE}/core/include/ -I${RIOTBASE}/sys/include/ -I${RIOTBASE}/drivers/include/ -I$(RIOTBASE)/drivers/cc110x_ng/include

include $(RIOTBASE)/Makefile.include

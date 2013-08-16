####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../RIOT
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT=sixlowpan

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD=msba2
endif

ifneq (,$(findstring msb-430,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../RIOT
export RIOTBOARD =$(CURDIR)/../boards

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

## Modules to include. 

USEMODULE += shell
USEMODULE += uart0
USEMODULE += posix
USEMODULE += vtimer
USEMODULE += auto_init
USEMODULE += timex
USEMOUDLE += net_help
USEMODULE += sixlowpan
USEMODULE += transceiver 
ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
else ifeq ($(BOARD),native)
	USEMODULE += nativenet
endif

export INCLUDES=-I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/drivers/cc110x_ng/include/ -I$(RIOTBASE)/sys/net/sixlowpan/include/

include $(RIOTBASE)/Makefile.include
endif

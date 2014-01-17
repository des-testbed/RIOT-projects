####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT =test_pnet

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTBOARD =$(RIOTBASE)/boards

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

## Modules to include. 

USEMODULE += auto_init
USEMODULE += posix
USEMODULE += pnet
USEMODULE += vtimer
ifeq ($(strip $(BOARD)),native)
	USEMODULE += nativenet
else ifeq ($(strip $(BOARD)),msba2)
	USEMODULE += cc110x_ng
endif

CFLAGS += -isystem $(RIOTBASE)/sys/net/include \
		  -isystem $(RIOTBASE)/sys/posix/pnet/include

include $(RIOTBASE)/Makefile.include
export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include \
				  -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib \
				  -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/drivers/include \


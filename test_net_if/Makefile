####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT = test_net_if

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

## Modules to include.

USEMODULE += net_if
ifeq ($(BOARD),native)
	USEMODULE += nativenet
else ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
	USEMODULE += auto_init
	INCLUDES += -I$(RIOTBASE)/drivers/cc110x_ng/include
endif

export INCLUDES += -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/sys/net/include

include $(RIOTBASE)/Makefile.include

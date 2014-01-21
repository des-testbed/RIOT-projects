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

BOARD_WHITELIST := telosb wsn430-v1_4 
BOARD_BLACKLIST :=  

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = telosb
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

QUIET = 1

## Modules to include.

USEMODULE += auto_init
USEMODULE += transceiver
USEMODULE += cc2420

INCLUDES += -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/drivers/cc2420/include

include $(RIOTBASE)/Makefile.include


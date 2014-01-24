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
	export BOARD = agile_fox
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

QUIET = 1

## Modules to include.

USEMODULE += auto_init
USEMODULE += transceiver
USEMODULE += ieee802154
USEMODULE += at86rf231

INCLUDES += -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/sys/net/include -I$(RIOTBASE)/drivers/at86rf231/include

include $(RIOTBASE)/Makefile.include


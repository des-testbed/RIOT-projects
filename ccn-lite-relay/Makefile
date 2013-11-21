####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT=ccn-lite-relay

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD=native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT

## Modules to include. 

USEMODULE += uart0
USEMODULE += posix

USEMODULE += auto_init

USEMODULE += transceiver
ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
else ifeq ($(BOARD),native)
	USEMODULE += nativenet
endif

USEMODULE += rtc
USEMODULE += ccn_lite
USEMODULE += crypto
USEMODULE += bloom
USEMODULE += hashes

export INCLUDES=-I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/drivers/cc110x_ng/include/ -I$(RIOTBASE)/sys/net/ccn_lite/include/

include $(RIOTBASE)/Makefile.include

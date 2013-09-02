####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT =test_bloom

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = msba2
endif

ifneq (,$(findstring msb-430,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else
# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTBOARD =$(CURDIR)/../../boards

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

## Modules to include.

USEMODULE += hashes
USEMODULE += bloom

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

export PROJDEPS = sets.h

include $(RIOTBASE)/Makefile.include
endif

sets.h: generate_sets.py words.txt.gz
	./generate_sets.py 10000 20

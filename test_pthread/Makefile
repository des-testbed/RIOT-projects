####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT = test_pthread

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = msba2
endif

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

## Modules to include. 


USEMODULE += posix

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTCPU)/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/ -I$(RIOTBASE)/sys/posix/include/ 

include $(RIOTBASE)/Makefile.include

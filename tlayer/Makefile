####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../../RIOT 
#### ../../boards   for board definitions (if you have one or more)
#### 

# name of your project
export PROJECT =tlayer

# for easy switching of boards
export BOARD = msba2

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT
export RIOTCPU =$(CURDIR)/../../RIOT/cpu
export RIOTBOARD =$(CURDIR)/../../boards

## Modules to include. 

USEMODULE += auto_init
USEMODULE += vtimer
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += config
USEMODULE += cc110x_ng
USEMODULE += net_help
USEMODULE += sixlowpan
USEMODULE += destiny
USEMODULE += uart0
USEMODULE += posix
USEMODULE += ltc4150

export INCLUDES += -I$(RIOTBASE)/sys/include -I$(RIOTBASE)/sys/net -I$(RIOTBASE)/drivers/include -I$(RIOTBASE)/drivers/cc110x_ng/include

include $(RIOTBASE)/Makefile.include

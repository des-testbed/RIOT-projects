debug: CFLAGS += -g
debug: CFLAGS += -DENABLE_DEBUG

# name of your project
export PROJECT = test_nativenet
#
# for easy switching of boards
export BOARD = native

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../RIOT

ifeq (,$(findstring native,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else

## Modules to include. 

USEMODULE += auto_init
USEMODULE += hwtimer
USEMODULE += nativenet
USEMODULE += transceiver

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include
debug: all

FORCE:
	touch main.c

sender: CFLAGS += -DSENDER
sender: PROJECT = test_nativenet_sender
sender: FORCE all

endif

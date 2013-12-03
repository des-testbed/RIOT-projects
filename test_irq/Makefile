valgrind: CFLAGS += -g
valgrind: CFLAGS += -DHAVE_VALGRIND_VALGRIND_H

# name of your project
export PROJECT = test_irq
#
# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

ifeq (,$(findstring native,$(BOARD)))
	include $(CURDIR)/../Makefile.unsupported
else

## Modules to include. 

USEMODULE += auto_init
USEMODULE += hwtimer
USEMODULE += uart0
USEMODULE += posix

# not yet working:
#
#USEMODULE += sht11
#USEMODULE += fat

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include
valgrind: all
endif

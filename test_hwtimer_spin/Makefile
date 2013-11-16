# define project name
export PROJECT = test_hwtimer_spin

# for easy switching of boards

# the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT

# modules to include
USEMODULE += auto_init
USEMODULE += hwtimer

export INCLUDES = -I$(RIOTBOARD)/$(BOARD)/include -I$(RIOTBASE)/core/include -I$(RIOTBASE)/cpu/$(CPU)/include -I$(RIOTBASE)/sys/lib -I$(RIOTBASE)/sys/include/ -I$(RIOTBASE)/drivers/include/

include $(RIOTBASE)/Makefile.include

export PROJECT = hello-world
include ../Makefile.applications_common

#These boards don't have LED_RED definitions:
export BOARD_BLACKLIST = chronos pttu mbed_lpc1768 redbee-econotag

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

USEMODULE += vtimer
USEMODULE += auto_init

include $(RIOTBASE)/Makefile.include

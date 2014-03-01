export PROJECT = hello-world
include ../Makefile.applications_common

# Boards with RED and GREEN LEDs:
export BOARD_WHITELIST = msba2 wsn430-v1_3b native wsn430-v1_4 avsextrem

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

USEMODULE += vtimer
USEMODULE += auto_init

include $(RIOTBASE)/Makefile.include

export PROJECT = hello-world
include ../Makefile.applications_common

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

USEMODULE += vtimer
USEMODULE += auto_init

include $(RIOTBASE)/Makefile.include

export PROJECT = sixlowpan
include ../Makefile.applications_common

# Boards that have cc110x_ng or nativenet support:
export BOARD_WHITELIST = native msba2 pttu avsextrem

USEMODULE += shell
USEMODULE += uart0
USEMODULE += posix
USEMODULE += vtimer
USEMODULE += auto_init
USEMODULE += timex
USEMOUDLE += net_help
USEMODULE += sixlowpan
USEMODULE += semaphore
USEMODULE += transceiver 
ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
else ifeq ($(BOARD),native)
	USEMODULE += nativenet
endif

export INCLUDES += -I$(RIOTBASE)/sys/net/include

include $(RIOTBASE)/Makefile.include

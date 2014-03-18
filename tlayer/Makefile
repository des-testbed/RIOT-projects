export PROJECT = tlayer

include ../Makefile.applications_common

# Transceivers are only defined for these boards in this Makefile:
export BOARD_WHITELIST = msba2 native

USEMODULE += auto_init
USEMODULE += vtimer
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += config
USEMODULE += transceiver
USEMODULE += net_help
USEMODULE += sixlowpan
USEMODULE += semaphore
USEMODULE += destiny
USEMODULE += uart0
USEMODULE += posix
USEMODULE += ltc4150

ifeq ($(BOARD),native)
	USEMODULE += nativenet
endif
ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
endif

export INCLUDES += -I$(RIOTBASE)/sys/net/include -I$(RIOTBASE)/sys/net/transport_layer/destiny

include $(RIOTBASE)/Makefile.include

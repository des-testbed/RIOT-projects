export PROJECT = test_net_if
export BOARD ?= agile_fox
include ../Makefile.applications_common

# These boards have an at86rf231:
BOARD_WHITELIST = agile_fox

USEMODULE += auto_init
USEMODULE += transceiver
USEMODULE += at86rf231

include $(RIOTBASE)/Makefile.include

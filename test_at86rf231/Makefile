export PROJECT = test_net_if
export BOARD ?= agilefox
include ../Makefile.applications_common

# These boards have an at86rf231:
BOARD_WHITELIST = agilefox

USEMODULE += auto_init
USEMODULE += transceiver
USEMODULE += at86rf231

include $(RIOTBASE)/Makefile.include

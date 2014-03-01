export PROJECT = lm75A-sensor-i2c
export BOARD ?= msba2
include ../Makefile.applications_common

# These boards have a GREEN LED and i2c:
export BOARD_WHITELIST = msba2 avsextrem

USEMODULE += i2c
USEMODULE += lm75a
USEMODULE += gpioint

include $(RIOTBASE)/Makefile.include

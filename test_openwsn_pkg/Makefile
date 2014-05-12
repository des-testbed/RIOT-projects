####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../RIOT
#### ../../boards   for board definitions (if you have one or more)
####

# name of your project
export PROJECT = test_openwsn_pkg

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD = iot-lab_M3
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

ifeq ($(BOARD),iot-lab_M3)
        include Makefile.$(BOARD)
endif

# Uncomment this to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
#CFLAGS += -DDEVELHELP

# Uncomment this to hide compiler invocation lines:
#QUIET = 1

USEPKG += openwsn

export INCLUDES += -I${RIOTBASE}/drivers/include/ \
					-I${RIOTBASE}/pkg/openwsn/RB-1.4/openwsn

include $(RIOTBASE)/Makefile.include

distclean: clean
	$(MAKE) -C $(RIOTBASE)/pkg/$(USEPKG) distclean

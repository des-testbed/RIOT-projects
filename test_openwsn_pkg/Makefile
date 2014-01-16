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
	export BOARD = telosb
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE = $(CURDIR)/../../RIOT

# uncomment this to enable scheduler statistics for ps
#CFLAGS += -DSCHEDSTATISTICS

# If you want to use valgrind, you should recompile native with either
# HAVE_VALGRIND_H or HAVE_VALGRIND_VALGRIND_H depending on the location
# of the valgrind header (i.e. <valgrind.h> or <valgrind/valgrind.h>)
# For more information about the valgrind support of RIOT read:
# RIOT/cpu/native/README
#CFLAGS += -DHAVE_VALGRIND_VALGRIND_H
#CFLAGS += -DHAVE_VALGRIND_H

# Uncomment this to enable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
#CFLAGS += -DDEVELHELP

# Uncomment this to hide compiler invocation lines:
#QUIET = 1

EXTERNAL_MODULES+=$(RIOTBASE)/pkg/openwsn
USEMODULE += openwsn

export INCLUDES += -I${RIOTBASE}/core/include/ -I${RIOTBASE}/sys/include/ -I${RIOTBASE}/drivers/include/ -I${RIOTBASE}/pkg/openwsn/RB-1.4/openwsn

# build: fetch all
# 	
# fetch:
# 	make -C $(RIOTBASE)/pkg/openwsn patch

export PROJDEPS = openwsn.h

include $(RIOTBASE)/Makefile.include

openwsn.h:
	$(MAKE) -C $(EXTERNAL_MODULES) patch

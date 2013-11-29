####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../RIOT 
#### ../../boards   for board definitions (if you have one or more)
####

# name of your project
export PROJECT = test_crypto

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
    export BOARD = native
endif

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT

# list here all modules that are used in your project
USEMODULE += posix
USEMODULE += uart0
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += auto_init
USEMODULE += crypto_3des
USEMODULE += crypto_aes
USEMODULE += crypto_rc5
USEMODULE += crypto_skipjack
USEMODULE += crypto_twofish
USEMODULE += crypto_sha256

export INCLUDES = -I${RIOTBASE}/core/include/ -I${RIOTBASE}/sys/include/ -I${RIOTBASE}/drivers/include/

include $(RIOTBASE)/Makefile.include

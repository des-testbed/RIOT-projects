####
#### Sample Makefile for building apps with the RIOT OS
####
#### The Sample Filesystem Layout is:
#### /this makefile
#### ../RIOT
#### ../../boards   for board definitions (if you have one or more)
#### 

QUIET ?= 1
USE_SHELL ?= 1
PAN_ID ?= 0xabcd
CHANNEL ?= 11
EUI64 ?= "20:14:02:20:AA:BB:CC:DD"
DATA ?= "$(shell for i in $$(seq 1280); do printf "\\%03o" $$(( (i % 255) + 1 )); done; echo "" )"

# name of your project
export PROJECT=6lpplugtest

# for easy switching of boards
ifeq ($(strip $(BOARD)),)
	export BOARD=native
endif

ifneq (,$(findstring msb-430,$(BOARD)))
include $(CURDIR)/../Makefile.unsupported
else

# this has to be the absolute path of the RIOT-base dir
export RIOTBASE =$(CURDIR)/../../RIOT

ifeq ($(BOARD),stm32f4discovery)
	include Makefile.$(BOARD)
endif

ifeq ($(FORMAT),1)
	CFLAGS += -DFORMAT -DTEST1
else ifeq ($(FORMAT),2)
	CFLAGS += -DFORMAT -DTEST2
else ifeq ($(FORMAT),3)
	CFLAGS += -DFORMAT -DTEST3
else ifeq ($(FORMAT),4)
	CFLAGS += -DFORMAT -DTEST4
else ifeq ($(FORMAT),5)
	CFLAGS += -DFORMAT -DTEST5
else ifeq ($(FORMAT),6)
	CFLAGS += -DFORMAT -DTEST6
else ifeq ($(FORMAT),7)
	CFLAGS += -DFORMAT -DTEST7
else ifeq ($(FORMAT),8)
	CFLAGS += -DFORMAT -DTEST8
endif

ifeq ($(HC),1)
	CFLAGS += -DHC -DTEST1
else ifeq ($(HC),2)
	CFLAGS += -DHC -DTEST2
else ifeq ($(HC),3)
	CFLAGS += -DHC -DTEST3
else ifeq ($(HC),4)
	CFLAGS += -DHC -DTEST4
else ifeq ($(HC),5)
	CFLAGS += -DHC -DTEST5
else ifeq ($(HC),6)
	CFLAGS += -DHC -DTEST6
else ifeq ($(HC),7)
	CFLAGS += -DHC -DTEST7
else ifeq ($(HC),8)
	CFLAGS += -DHC -DTEST8
else ifeq ($(HC),9)
	CFLAGS += -DHC -DTEST9
else ifeq ($(HC),10)
	CFLAGS += -DHC -DTEST10
endif

ifeq ($(ND),1)
	IPPREFIX ?= "abcd:ef01::/64"
	CFLAGS += -DND -DTEST1
else ifeq ($(ND),2)
	IPPREFIX ?= "abcd:ef01::/64"
	CFLAGS += -DND -DTEST2
else ifeq ($(ND),3)
	IPPREFIX ?= "abcd:ef01::/64"
	CFLAGS += -DND -DTEST3
else ifeq ($(ND),4)
	IPPREFIX ?= "abcd:ef01::/64"
	CFLAGS += -DND -DTEST4
else ifeq ($(ND),5)
	IPPREFIX ?= "abcd:ef01::/64"
	CFLAGS += -DND -DTEST5
else ifeq ($(ND),6)
	IPPREFIX ?= "abcd:ef01::/64 1234:6789::/64 1337::/64"
	CFLAGS += -DND -DTEST6 -DIPPREFIX_LEN=3
else ifeq ($(ND),7)
	IPPREFIX ?= "abcd:ef01::/64 1234:6789::/64 1337::/64"
	CFLAGS += -DND -DTEST7 -DIPPREFIX_LEN=3
endif

ifeq ($(ND_HC),1)
	CFLAGS += -DND_HC -DTEST1
else ifeq ($(ND_HC),2)
	CFLAGS += -DND_HC -DTEST2
else ifeq ($(ND_HC),3)
	CFLAGS += -DND_HC -DTEST3
else ifeq ($(ND_HC),4)
	CFLAGS += -DND_HC -DTEST4
endif

ifeq ($(EUT),1)
	CFLAGS += -DEUT1
	DEST ?= "fe80::ff:fe00:2"
else ifeq ($(EUT),2)
	CFLAGS += -DEUT2 -DCONF_RADIO_ADDR=2
	DEST ?= "fe80::ff:fe00:1"
endif

ifneq ($(DEST),)
	CFLAGS += -DDEST=\"$(DEST)\"
endif

ifneq ($(DATA),)
	CFLAGS += -DDATA=\"$(DATA)\"
endif

ifneq ($(CHANNEL),)
	CFLAGS += -DCHANNEL=$(CHANNEL)
endif

ifneq ($(EUI64),)
	CFLAGS += -DEUI64=\"$(EUI64)\"
endif

ifneq ($(PAN_ID),)
	CFLAGS += -DPAN_ID=$(PAN_ID)
endif

## Modules to include. 
ifneq (,$(filter -DHC,$(CFLAGS)))
	ifneq (,$(filter -DTEST5 -DTEST6 -DTEST7 -DTEST8,$(CFLAGS)))
		IPPREFIX ?= "abcd:ef01::/64"
		USEPKG += libcoap
	endif
endif

ifneq ($(IPPREFIX),)
	CFLAGS += -DIPPREFIX=\"$(IPPREFIX)\"
endif

ifeq ($(USE_SHELL),1)
	IPPREFIX ?= "abcd:ef01::/64"
	USEPKG += libcoap
	USEMODULE += shell
	USEMODULE += shell_commands
	USEMODULE += posix
endif

USEMODULE += auto_init
USEMODULE += sixlowpan
USEMODULE += vtimer

ifeq ($(BOARD),msba2)
	USEMODULE += cc110x_ng
else ifeq ($(BOARD),iot-lab_M3)
	USEMODULE += at86rf231
else ifeq ($(BOARD),native)
	USEMODULE += nativenet
endif

export INCLUDES = -I$(RIOTBASE)/sys/net/include \
				  -I$(RIOTBASE)/sys/posix/pnet/include

include $(RIOTBASE)/Makefile.include

clean-app: clean-shell clean
	rm -rf format*.elf
	rm -rf hc*.elf
	rm -rf nd*.elf
	rm -rf nd-hc*.elf
	make -C $(RIOTBASE)/pkg/libcoap distclean

clean-shell: clean-format clean-hc clean-nd clean-nd-hc 
	rm -rf bin/$(BOARD)/$(PROJECT)/test_shell.o

clean-format: clean-autoinit
	rm -rf bin/$(BOARD)/$(PROJECT)/test_format.o \
           bin/$(BOARD)/$(PROJECT)/main.o

clean-hc: clean-autoinit
	rm -rf bin/$(BOARD)/$(PROJECT)/test_hc.o \
           bin/$(BOARD)/$(PROJECT)/main.o

clean-nd: clean-autoinit
	rm -rf bin/$(BOARD)/$(PROJECT)/test_nd.o \
           bin/$(BOARD)/$(PROJECT)/main.o

clean-nd-hc: clean-autoinit
	rm -rf bin/$(BOARD)/$(PROJECT)/test_nd_hc.o \
           bin/$(BOARD)/$(PROJECT)/main.o

clean-autoinit:
	rm -rf bin/$(BOARD)/auto_init.[ao]

endif
